/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMCMGIft.h
 *  Date        : 2019_0726
 *  Description : BSIMCMG data structures
 */


#include "omiIft.h"


/* This macro gets omiBSIMCMGWorkData offset of a field */
#define OMI_BSIMCMG_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiBSIMCMGWorkData, _field_)

/* This structure defines BSIMCMG work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiBSIMCMGWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_BSIMCMG_STD_NODE_SIZE_MAX];
} omiBSIMCMGWorkData;


/* This structure defines BSIMCMG instance specific data */
typedef struct omiBSIMCMGSpecData
{
  /* BSIMCMG node number */
  int node[OMI_BSIMCMG_STD_NODE_SIZE_MAX];
  /* BSIMCMG node map */
  int map [OMI_BSIMCMG_STD_NODE_SIZE_MAX];

} omiBSIMCMGSpecData;

int omiBSIMCMGNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiBSIMCMGIft.h,v $ */
