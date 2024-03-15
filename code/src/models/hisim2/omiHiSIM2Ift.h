/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIM2Ift.h
 *  Date        : 2019_0726
 *  Description : HiSIM2 data structures
 */


#include "omiIft.h"


/* This macro gets omiHiSIM2WorkData offset of a field */
#define OMI_HiSIM2_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiHiSIM2WorkData, _field_)

/* This structure defines HiSIM2 work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiHiSIM2WorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_HiSIM2_STD_NODE_SIZE_MAX];
} omiHiSIM2WorkData;


/* This structure defines HiSIM2 instance specific data */
typedef struct omiHiSIM2SpecData
{
  /* HiSIM2 node number */
  int node[OMI_HiSIM2_STD_NODE_SIZE_MAX];
  /* HiSIM2 node map */
  int map [OMI_HiSIM2_STD_NODE_SIZE_MAX];

} omiHiSIM2SpecData;

int omiHiSIM2Noise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiHiSIM2Ift.h,v $ */
