/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Ift.h
 *  Date        : 2010_1123
 *  Description : BSIM4 data structures
 */


#include "omiIft.h"


/* This macro gets omiBSIM4WorkData offset of a field */
#define OMI_BSIM4_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiBSIM4WorkData, _field_)

#define OMI_BSIM4_NEW_NODE_SIZE_MAX  1	/* maximum BSIM4 new node size, set 2 in this sample */


/* This enumerates all of BSIM4 new nodes */
typedef enum omiBSIM4NewNode
{
  omiBSIM4n0 = OMI_BSIM4_STD_NODE_SIZE_MAX,	/* 0, new node n0 */
} omiBSIM4NewNode;


/* This structure defines BSIM4 work data V/I/G/Q/C, which must be double */
typedef struct omiBSIM4WorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_BSIM4_STD_NODE_SIZE_MAX + OMI_BSIM4_NEW_NODE_SIZE_MAX];
  /* The following entries are just examples for V/I/G/Q/C information,
     which could be added, removed or redefined by model developers.  */
  double In0xd, In0xd_n0xd;     /* current & its derivatives */
  double In0xs, In0xs_n0xs;     /* current & its derivatives */
  double Qn0xd, Qn0xd_n0xd;		/* charge & its derivatives */
  double Qn0xs, Qn0xs_n0xs;		/* charge & its derivatives */
} omiBSIM4WorkData;
/* Only the first field is assigned by simulators for node voltages and others are assigned by OMI libraries. */

/* This structure defines BSIM4 instance specific data */
typedef struct omiBSIM4SpecData
{
  /* BSIM4 node number */
  int node[OMI_BSIM4_STD_NODE_SIZE_MAX + OMI_BSIM4_NEW_NODE_SIZE_MAX];
  /* BSIM4 node map */
  int map [OMI_BSIM4_STD_NODE_SIZE_MAX + OMI_BSIM4_NEW_NODE_SIZE_MAX];

  int newNodeSize;				/* number of new node */
  double Gn0xb;				    	/* constant conductance */
} omiBSIM4SpecData;


int omiBSIM4Evaluate (void *pModelData, void *pInstData, omiEvalData *pEvalData);
int omiBSIM4Noise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiBSIM4Ift.h,v $ */
