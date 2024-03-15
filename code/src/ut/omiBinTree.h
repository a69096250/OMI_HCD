/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBinTree.h
 *  Date        : 2010_1123
 *  Description : Binary tree
 */


#ifndef BINTREE_H
#define BINTREE_H

typedef struct parNode parNode;

struct parNode
{
  String  name;
  ParamId id;
  int     bf; /* the balance factor of this node*/
  parNode *left;
  parNode *right;
  parNode *parent;
}; 

#ifdef __STDC__
void omiInsertNode(parNode **pHeader, String aName, ParamId aParamId);
ParamId omiGetNode(parNode *pHeader, String aName);
#else
void omiInsertNode();
ParamId omiGetNode();
#endif

#endif /* BINTREE_H */


/* end of $RCSfile: omiBinTree.h,v $ */
