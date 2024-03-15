/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiHash.c
 *  Date        : 2010_1123
 *  Description : This file provide functions to create table,
 *                enter element, find element & destory table.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "omiHash.h"


#define ALIGN_MEM_SIZE 8
#define MEM_CHUNK_SIZE 64*1024

/* This function is used for memory pool */
static char *
allocate_from_elem_chunk(pHashTable tbl)
{
    elem_mem_chunk *cur_elem_chunk_p;
    int size;

    size = (sizeof(Element) % ALIGN_MEM_SIZE) ? ALIGN_MEM_SIZE*((sizeof(Element)/ALIGN_MEM_SIZE)+1): sizeof(Element); /* on a word boundary */

    if ((tbl->next_chunk_loc + size > MEM_CHUNK_SIZE) || tbl->first_chunk )
    {
        tbl->current_chunk  = (char *) malloc(MEM_CHUNK_SIZE );
        tbl->cur_chunk_loc = 0;

        cur_elem_chunk_p = (elem_mem_chunk *) malloc (sizeof (elem_mem_chunk) );

        if (tbl->first_chunk)
        {
            cur_elem_chunk_p->mem_chunk = tbl->current_chunk;
            cur_elem_chunk_p->next = NULL;
            tbl->elem_mem_list = cur_elem_chunk_p;
            tbl->first_chunk = 0;
        }
        else
        {
            cur_elem_chunk_p->mem_chunk = tbl->current_chunk;
            cur_elem_chunk_p->next = tbl->elem_mem_list;
            tbl->elem_mem_list = cur_elem_chunk_p;
        }
    }
    else
    {
        tbl->cur_chunk_loc = tbl->next_chunk_loc;
    }

    tbl->next_chunk_loc = tbl->cur_chunk_loc + size;

    return(&tbl->current_chunk[tbl->cur_chunk_loc]);
}


pHashTable
omiHashCreate(unsigned int count, void (*free_element_func) (char *, void *))
{
    unsigned num_segments;
    pHashTable tbl = NULL;
    unsigned i;

/*
 * Adjust count to be nearest higher power of 2, minimum SEGSIZE,
 * then convert into segments.
 */
    for (i = SEGSIZE; i < count; i <<= 1)
        ;

    num_segments = i / SEGSIZE;

    if (num_segments > DIRSIZE)
        num_segments = DIRSIZE;

    tbl = (pHashTable) calloc(1, sizeof(HashTable));
    if (!tbl)
    {
        fputs ("error: run out of memory.\n", stderr);
        exit (1);
    }

    tbl->seg_count  = 0;
    tbl->p          = 0;
    tbl->key_count  = 0;
/*
 * Allocate initial "num_segments" # of segments of buckets
 */
    for (i = 0; i < num_segments; i++)
    {
        tbl->dir[i] = (pElement *) calloc(SEGSIZE, sizeof(pElement));
        if (!tbl->dir[i])
        {
	    fputs ("error: run out of memory.\n", stderr);
	    exit (1);
        }
        tbl->seg_count++;
    }
    tbl->max_p = num_segments * SEGSIZE;
    tbl->alloc_mem_from_mem_chunk = 1; /*user memory pool to improve performance */
    tbl->next_chunk_loc = 0;
    tbl->current_chunk = NULL;
    tbl->cur_chunk_loc = 0;
    tbl->first_chunk = 1;
    tbl->current_elem = NULL;
    tbl->first_elem = NULL;
    tbl->free_element_func = free_element_func;
#if DEBUG
    fprintf(stderr, "hcreate: table=%x count=%d num_seqments=%d max_p=%d seg_count=%d\n",
	    tbl, count, num_segments, tbl->max_p, tbl->seg_count);
#endif
#if HASH_STATISTICS
    tbl->find_accesses = 0;
    tbl->enter_accesses = 0;
    tbl->other_accesses = 0;
    tbl->find_collisions = 0;
    tbl->enter_collisions = 0;
    tbl->other_collisions = 0;
    tbl->expansions = 0;
#endif
    return tbl;
}


void
omiHashEnter(pHashTable tbl, char *key, void *data)
{
    HashValue  h=0;
    HashValue  segidx, segdir;
    pElement   *currseg;
    pElement   *p, q;
    unsigned char *k = (unsigned char *)key; 

    assert(tbl != NULL); /* Kinder really than return(NULL); */

#if HASH_STATISTICS
    tbl->enter_accesses++;
#endif
                         
    HASH(k,h);
    h = h % tbl->max_p;
    segdir = h / SEGSIZE;
    segidx = h % SEGSIZE;

#if DEBUG
    fprintf(stderr, "tbl %x key %s h %d\n", tbl, key, h);
#endif

/*
 * valid pElement ensured by HASH()
 */
    currseg = tbl->dir[segdir];
    assert(currseg != NULL);	/* bad failure if tripped */
    p = &currseg[segidx];
    q = *p;
/*
 * Follow collision chain
 */
    while (q != NULL && strcasecmp(q->key, key))
    {
        p = &q->next;
        q = *p;
#if HASH_STATISTICS
	tbl->enter_collisions++;
#endif
    }

    if (q != NULL)	       /* found */
    {
        if (tbl->free_element_func)
            tbl->free_element_func (q->key, q->data);
        q->key = key;
        q->data = data;
 	return;
    }

    q = (Element *) allocate_from_elem_chunk(tbl);
    if (!q)
    {
        fputs ("error: run out of memory.\n", stderr);
        exit (1);
    }
    tbl->key_count++;

    *p = q;		       /* link into chain */
/*
 * Initialize new element
 */
    q->key = key;
    q->data = data;
    q->next = NULL;
    q->next_elem = NULL;

    if (!tbl->first_elem)
      tbl->first_elem = q;
    else
      tbl->current_elem->next_elem = q;
    tbl->current_elem = q;

#if DEBUG
    fprintf(stderr, "tbl %x key %s data %x\n",
            q, q->key, q->data);
#endif

}


void *
omiHashFind(pHashTable tbl, char *key)
{
    HashValue  h=0;
    HashValue  segidx, segdir;
    pElement   *currseg;
    pElement    q;
    unsigned char *k = (unsigned char *)key; 
    assert(tbl != NULL); /* Kinder really than return(NULL); */

#if HASH_STATISTICS
    tbl->find_accesses++;
#endif
  
    HASH(k,h);
    h = h % tbl->max_p;

    segdir = h / SEGSIZE;
    segidx = h % SEGSIZE;

#if DEBUG
    fprintf(stderr, "segdir = %d, segidx = %d, h = %d \n", (int )segdir,
           (int )segidx, (int )h );
#endif

/*
 * valid pElement ensured by HASH()
 */
    currseg = tbl->dir[segdir];
    assert(currseg != NULL);	/* bad failure if tripped */
    q = currseg[segidx];
   
    while (q != NULL && strcasecmp(q->key, key))
    {
	q = q->next;
#if HASH_STATISTICS
	tbl->find_collisions++;
#endif
    }

    if (q != NULL)
    {   /* found */
#if DEBUG
        fprintf(stderr, "q %x q->data %s\n",
                q, q->data);
#endif
        return q->data;
    }
    else
        return (void *)NULL;
}


pElement
omiHashGet(pHashTable tbl, char **key, void **data, pElement *p)
{
    if (tbl != NULL)
    {
        if (!(*p))
            *p = tbl->first_elem;
        else
            *p = (*p)->next_elem;

        if (*p)
        {
            *key = (*p)->key;
            *data = (*p)->data;
        }
    }

    return *p;
}


void
omiHashDestroy(pHashTable tbl)
{
    unsigned i=0;
    Element   *p;
    elem_mem_chunk *next_mem_chunk_p = NULL;
    elem_mem_chunk *cur_mem_chunk_p = NULL;

    if (tbl != NULL)
    {
        if (tbl->free_element_func)
        {
            p = tbl->first_elem;
            while (p)
            {
                tbl->free_element_func (p->key, p->data);
                p = p->next_elem;
            }
        }
        tbl->first_elem = NULL;
        tbl->current_elem = NULL;

        cur_mem_chunk_p = tbl->elem_mem_list;
        while (cur_mem_chunk_p)
        {
	    next_mem_chunk_p = cur_mem_chunk_p->next;
	    free(cur_mem_chunk_p->mem_chunk);
	    cur_mem_chunk_p->mem_chunk = NULL;
	    free(cur_mem_chunk_p);
	    cur_mem_chunk_p = next_mem_chunk_p;
        }

        for (i = 0; i < tbl->seg_count; i++)
        {
             if (tbl->dir[i] != NULL)
             {
                 free(tbl->dir[i]);
                 tbl->dir[i] = NULL;
             }
        }
       
#if HASH_STATISTICS && DEBUG
        fprintf(stderr, "hash destroy:accesses: find=%ld enter=%ld other=%ld\n",
	        tbl->find_accesses,
	        tbl->enter_accesses,
	        tbl->other_accesses);
        fprintf(stderr, "hash destroy:collisions: find=%ld enter=%ld "
	        "other=%ld\n",
	        tbl->find_collisions,
	        tbl->enter_collisions,
	        tbl->other_collisions);
        fprintf(stderr, "hdestroy: expansions %ld\n",
	        tbl->expansions);
        fprintf(stderr, "keys %ld max_p %d seg_count %d\n",
	        tbl->key_count, tbl->max_p,
	        tbl->seg_count);
#endif
        free(tbl);
        tbl = NULL;
    }
}
