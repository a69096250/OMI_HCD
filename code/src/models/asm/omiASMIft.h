/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASMIft.h
 *  Date        : 2019_0726
 *  Description : ASM data structures
 */


#include "omiIft.h"


/* This macro gets omiASMWorkData offset of a field */
#define OMI_ASM_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiASMWorkData, _field_)

/* This structure defines ASM work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiASMWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_ASM_STD_NODE_SIZE_MAX];
} omiASMWorkData;


/* This structure defines ASM instance specific data */
typedef struct omiASMSpecData
{
  /* ASM node number */
  int node[OMI_ASM_STD_NODE_SIZE_MAX];
  /* ASM node map */
  int map [OMI_ASM_STD_NODE_SIZE_MAX];

} omiASMSpecData;

int omiASMNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiASMIft.h,v $ */
