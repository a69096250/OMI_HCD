/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIMHVIft.h
 *  Date        : 2019_0726
 *  Description : HiSIMHV data structures
 */


#include "omiIft.h"


/* This macro gets omiHiSIMHVWorkData offset of a field */
#define OMI_HiSIMHV_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiHiSIMHVWorkData, _field_)

/* This structure defines HiSIMHV work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiHiSIMHVWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_HiSIMHV_STD_NODE_SIZE_MAX];
} omiHiSIMHVWorkData;


/* This structure defines HiSIMHV instance specific data */
typedef struct omiHiSIMHVSpecData
{
  /* HiSIMHV node number */
  int node[OMI_HiSIMHV_STD_NODE_SIZE_MAX];
  /* HiSIMHV node map */
  int map [OMI_HiSIMHV_STD_NODE_SIZE_MAX];

} omiHiSIMHVSpecData;

int omiHiSIMHVNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiHiSIMHVIft.h,v $ */
