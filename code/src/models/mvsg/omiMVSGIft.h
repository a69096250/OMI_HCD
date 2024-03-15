/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiMVSGIft.h
 *  Date        : 2019_0726
 *  Description : MVSG data structures
 */


#include "omiIft.h"


/* This macro gets omiMVSGWorkData offset of a field */
#define OMI_MVSG_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiMVSGWorkData, _field_)

/* This structure defines MVSG work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiMVSGWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_MVSG_STD_NODE_SIZE_MAX];
} omiMVSGWorkData;


/* This structure defines MVSG instance specific data */
typedef struct omiMVSGSpecData
{
  /* MVSG node number */
  int node[OMI_MVSG_STD_NODE_SIZE_MAX];
  /* MVSG node map */
  int map [OMI_MVSG_STD_NODE_SIZE_MAX];

} omiMVSGSpecData;

int omiMVSGNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiMVSGIft.h,v $ */
