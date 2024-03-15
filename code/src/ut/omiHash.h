/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiHash.h
 *  Date        : 2010_1123
 *  Description : Hash table
 */


#ifndef OMIHASH_H
#define OMIHASH_H

/*
#define HASH_STATISTICS 1
#define DEBUG 1
*/
/* Constants */
#define SEGSIZE	2048   /* should be power of 2 for speed */
#define DIRSIZE	1024   /* should be power of 2 for speed */

#define HASH(k, h) \
        while (*k != '\0')           \
        {                            \
       	    h = (h << 5) + h + *k++; \
        }                            \


/*

       Element
    +---------------+
    | key           |                 Segment
    +---------------+              +--------------+
    | data          | <------------|              |
    +---------------+              +--------------+
    | next          |
    +---------------+






            dir                  segment              element
      ^  +------------+        +-----------+       +-----------+
      |  |            |------->|           |------>|           |
      |  +------------+        +-----------+       |           |
      |  |            |        |           |       |           |
      |  +------------+        +-----------+       +-----------+
      |  |            |        |           |
      |  +------------+	       +-----------+
      |  |            |        |           |
      |  +------------+	       +-----------+
      |  |            | SEGSIZE|           |
      |  +------------+	       +-----------+
      |  |            |        |           |
      |  +------------+	       +-----------+
      |  |            |        |           |
 DIRSIZE +------------+	       +-----------+
      |  |            |        |           |
      |  +------------+	       +-----------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      |  +------------+
      |  |            |
      V  +------------+


*/

#ifdef _WIN32
#define strcasecmp stricmp
#endif /* _WIN32 */

typedef struct Element
{
    char	   *key;
    void	   *data;
    struct Element *next;
    struct Element *next_elem;
} Element, *pElement;

typedef unsigned long HashValue;

typedef struct elem_mem_chunk {
    char* mem_chunk;
    struct elem_mem_chunk *next;
} elem_mem_chunk;

typedef struct HashTable
{
  
    long 	    p;		/* next bucket to be split */
    long 	    max_p;	/* upper bound on p during expansion */
    unsigned int    key_count;	/* current # keys */
    unsigned int    seg_count;	/* current # segments */
       
    int             alloc_mem_from_mem_chunk;
    int             next_chunk_loc;
    char           *current_chunk;
    int             cur_chunk_loc;
    int             first_chunk;
    elem_mem_chunk *elem_mem_list;
    pElement       *dir[DIRSIZE];
    pElement        current_elem;
    pElement        first_elem;
    void 	  (*free_element_func) (char *, void *);
#ifdef HASH_STATISTICS
    long	    find_accesses;
    long	    enter_accesses;
    long	    other_accesses;
    long	    find_collisions;
    long	    enter_collisions;
    long	    other_collisions;
    long	    expansions;
#endif
} HashTable, *pHashTable;


#ifdef __STDC__
extern pHashTable  omiHashCreate (unsigned int, void (*free_element_func) (char *, void *));
extern void        omiHashEnter (pHashTable, char *, void *);
extern void       *omiHashFind  (pHashTable, char *);
extern pElement    omiHashGet (pHashTable tbl, char **key, void **data, pElement *p);
extern void        omiHashDestroy (pHashTable);
#else
extern pHashTable  omiHashCreate ();
extern void        omiHashEnter ();
extern void       *omiHashFind  ();
extern pElement    omiHashGet ();
extern void        omiHashDestroy ();
#endif


#endif /* OMIHASH_H */
