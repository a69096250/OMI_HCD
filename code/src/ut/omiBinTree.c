/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBinTree.c
 *  Date        : 2010_1123
 *  Description : This file provide functions to build a AVL tree;
 *                Only insert node and lookup node operation/function
 *                are provided, because the application here does not
 *                need delete node operation.
 */


#include <stdlib.h>
#include <string.h>
#include "omiDef.h"
#include "omiBinTree.h"

#ifdef _WIN32
#define strcasecmp stricmp
#endif /* _WIN32 */


static void omiAdjustBF(parNode *from, parNode *to);

void omiInsertNode(parNode **pHeader, String aName, ParamId aParamId)
{
    parNode  *tmpNode, *newNode, *lastNode, *nodeA, *subRoot;
    parNode  *parentA, *nodeB, *nodeCL, *nodeCR;
    int compstr = 0, length;
    int direct1, direct2;
    /* left equals 1 and right equals -1 */

    nodeA = NULL;
    direct1 = 0;
    direct2 = 0;
    tmpNode = *pHeader;
    lastNode = *pHeader;
    /* first, check whether need add this node
       and recode node A if existed */

    while (tmpNode != NULL)
    {
        compstr = strcasecmp(aName, tmpNode->name);
        if (compstr == 0)
        {
            /* the node has existed */
            return;
        }
        else
        {
            lastNode = tmpNode;
            if (compstr < 0)
            {
                if (tmpNode->bf == 1 || tmpNode->bf == -1)
                {
                    nodeA = tmpNode;
                    direct1 = 1;
                }
                tmpNode = tmpNode->left;
            }
            else
            {
                if (tmpNode->bf == 1 || tmpNode->bf == -1)
                {
                    nodeA = tmpNode;
                    direct1 = -1;
                }
                tmpNode = tmpNode->right;
            }
            
        }
    }

    /* generate the new node */
    newNode = (parNode *)malloc(sizeof(parNode));
    newNode->id = aParamId;
    newNode->bf = 0;
    length = strlen(aName);
    newNode->name = (String)malloc((length + 1) * sizeof(char));
    strcpy(newNode->name, aName);
    newNode->name[length] = '\0';
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (lastNode == NULL)
    {
        /* the binary tree is null */
        *pHeader = newNode;
        return;
    }
    /* add this node into binary tree */
    if (compstr < 0)
        lastNode->left = newNode;
    else if (compstr > 0)
        lastNode->right = newNode;
    newNode->parent = lastNode;

    /* if node A does not exist, modify all passed nodes'
       balance factor */ 
    if (nodeA == NULL)
    {
        omiAdjustBF(newNode, *pHeader);
        return;
    }

    /* need not rotation the AVL tree */
    if (nodeA->bf * direct1 == -1)
    {
        omiAdjustBF(newNode, nodeA);
        nodeA->bf = 0;
        return;
    } 

    /* need rotation the AVL tree */
    if (direct1 == 1)
        compstr = strcasecmp(aName, (nodeA->left)->name);
    else if (direct1 == -1)
        compstr = strcasecmp(aName, (nodeA->right)->name);
    if (compstr < 0)
        direct2 = 1;
    else
        direct2 = -1;

    /* four cases: (direct1, direct2)
       LL(1, 1) LR(1, -1) RL(-1, 1) RR(-1, -1) */
    if (direct1 * direct2 == 1)
    {
    /* for LL and RR, only need a single rotation */
        if (direct1 == 1)
            subRoot = nodeA->left;
        else
            subRoot = nodeA->right;
        parentA = nodeA->parent; 
        if (parentA == NULL)
        {
            *pHeader = subRoot;
            subRoot->parent = NULL;
        }
        else
        {
            if (parentA->left == nodeA)
                parentA->left = subRoot;
            else
                parentA->right = subRoot;
            subRoot->parent = parentA;
        }
        if (direct1 == 1)
        {
            nodeA->left = subRoot->right;
            if (nodeA->left != NULL)
                (nodeA->left)->parent = nodeA;
            subRoot->right = nodeA;
            nodeA->parent = subRoot;
        }
        else
        {
            nodeA->right = subRoot->left;
            if (nodeA->right != NULL)
                (nodeA->right)->parent = nodeA;
            subRoot->left = nodeA;
            nodeA->parent = subRoot;
        }
        nodeA->bf = 0;
        omiAdjustBF(newNode, subRoot);
        subRoot->bf = 0; 
        return;
    }
    {
    /* for LR and RL, need a double rotation */
        if (direct1 == 1)
        {
            nodeB = nodeA->left;
            subRoot = nodeB->right;
        }
        else
        {
            nodeB = nodeA->right;
            subRoot = nodeB->left;
        }
        nodeCL = subRoot->left;
        nodeCR = subRoot->right;
        omiAdjustBF(newNode, subRoot);
        parentA = nodeA->parent;
        if (parentA == NULL)
        {
            *pHeader = subRoot;
            subRoot->parent = NULL;
        }
        else
        {
            if (parentA->left == nodeA)
                parentA->left = subRoot;
            else
                parentA->right = subRoot;
            subRoot->parent = parentA;
        }
        if (direct1 == 1)
        {
            subRoot->left = nodeB;
            subRoot->right = nodeA;
            nodeA->parent = subRoot;
            nodeB->parent = subRoot;
            nodeB->right = nodeCL;
            if (nodeCL != NULL)
                nodeCL->parent = nodeB;
            nodeA->left = nodeCR;
            if (nodeCR != NULL)
                nodeCR->parent = nodeA;
        }
        else
        {
            subRoot->left = nodeA;
            subRoot->right = nodeB;
            nodeA->parent = subRoot;
            nodeB->parent = subRoot;
            nodeA->right = nodeCL;
            if (nodeCL != NULL)
                nodeCL->parent = nodeA;
            nodeB->left = nodeCR;
            if (nodeCR != NULL)
                nodeCR->parent = nodeB;
        }
        if (subRoot->bf == 0)
        {
            nodeA->bf = 0;
            nodeB->bf = 0;
        }
        else if (subRoot->bf == 1)
        {
            nodeA->bf = -1;
            nodeB->bf = 0;
        }
        else if (subRoot->bf == -1)
        {
            nodeA->bf = 0;
            nodeB->bf = 1;
        }
    }
    return;
}


ParamId omiGetNode(parNode *pHeader, String aName)
{
    parNode  *tmpNode;
    int compstr;

    tmpNode = pHeader;
    while (tmpNode != NULL)
    {
        compstr = strcasecmp(aName, tmpNode->name);
        if (compstr == 0)
            return tmpNode->id;
        else if (compstr < 0)
            tmpNode = tmpNode->left;
        else
            tmpNode = tmpNode->right; 
    }

    /* the node does not exist */
    return OMI_BADPARAM;
}


/* adjust the nodes' balance factor. node "from"'s bf would
   not be modified while "to"'s would be */
static void omiAdjustBF(parNode *from, parNode *to)
{
    parNode *tmp;

    tmp = from;
    while (tmp != to && tmp->parent != NULL)
    {
        if (tmp == (tmp->parent)->left)
        {
        /* new node is added into the left child tree*/
            (tmp->parent)->bf += 1;
        }
        else
        {
        /* new node is added into the right child tree*/
            (tmp->parent)->bf -= 1;
        }
        tmp = tmp->parent;
    }
}


/* end of $RCSfile: omiBinTree.c,v $ */
