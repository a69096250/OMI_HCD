/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMBULKIft.h
 *  Date        : 2019_0726
 *  Description : BSIMBULK data structures
 */


#include "omiIft.h"


/* This macro gets omiBSIMBULKWorkData offset of a field */
#define OMI_BSIMBULK_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiBSIMBULKWorkData, _field_)

/* This structure defines BSIMBULK work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiBSIMBULKWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_BSIMBULK_STD_NODE_SIZE_MAX];
} omiBSIMBULKWorkData;


/* This structure defines BSIMBULK instance specific data */
typedef struct omiBSIMBULKSpecData
{
  /* BSIMBULK node number */
  int node[OMI_BSIMBULK_STD_NODE_SIZE_MAX];
  /* BSIMBULK node map */
  int map [OMI_BSIMBULK_STD_NODE_SIZE_MAX];

} omiBSIMBULKSpecData;

int omiBSIMBULKNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiBSIMBULKIft.h,v $ */
