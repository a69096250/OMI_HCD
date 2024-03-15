/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMIMGIft.h
 *  Date        : 2019_0726
 *  Description : BSIMIMG data structures
 */


#include "omiIft.h"


/* This macro gets omiBSIMIMGWorkData offset of a field */
#define OMI_BSIMIMG_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiBSIMIMGWorkData, _field_)

/* This structure defines BSIMIMG work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiBSIMIMGWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_BSIMIMG_STD_NODE_SIZE_MAX];
} omiBSIMIMGWorkData;


/* This structure defines BSIMIMG instance specific data */
typedef struct omiBSIMIMGSpecData
{
  /* BSIMIMG node number */
  int node[OMI_BSIMIMG_STD_NODE_SIZE_MAX];
  /* BSIMIMG node map */
  int map [OMI_BSIMIMG_STD_NODE_SIZE_MAX];

} omiBSIMIMGSpecData;

int omiBSIMIMGNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiBSIMIMGIft.h,v $ */
