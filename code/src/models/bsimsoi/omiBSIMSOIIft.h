/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMSOIIft.h
 *  Date        : 2019_0726
 *  Description : BSIMSOI data structures
 */


#include "omiIft.h"


/* This macro gets omiBSIMSOIWorkData offset of a field */
#define OMI_BSIMSOI_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiBSIMSOIWorkData, _field_)

/* This structure defines BSIMSOI work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiBSIMSOIWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_BSIMSOI_STD_NODE_SIZE_MAX];
} omiBSIMSOIWorkData;


/* This structure defines BSIMSOI instance specific data */
typedef struct omiBSIMSOISpecData
{
  /* BSIMSOI node number */
  int node[OMI_BSIMSOI_STD_NODE_SIZE_MAX];
  /* BSIMSOI node map */
  int map [OMI_BSIMSOI_STD_NODE_SIZE_MAX];

} omiBSIMSOISpecData;

int omiBSIMSOINoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiBSIMSOIIft.h,v $ */
