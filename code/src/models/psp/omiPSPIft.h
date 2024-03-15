/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiPSPIft.h
 *  Date        : 2019_0726
 *  Description : PSP data structures
 */


#include "omiIft.h"


/* This macro gets omiPSPWorkData offset of a field */
#define OMI_PSP_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiPSPWorkData, _field_)

/* This structure defines PSP work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiPSPWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_PSP_STD_NODE_SIZE_MAX];
} omiPSPWorkData;


/* This structure defines PSP instance specific data */
typedef struct omiPSPSpecData
{
  /* PSP node number */
  int node[OMI_PSP_STD_NODE_SIZE_MAX];
  /* PSP node map */
  int map [OMI_PSP_STD_NODE_SIZE_MAX];

} omiPSPSpecData;

int omiPSPNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiPSPIft.h,v $ */
