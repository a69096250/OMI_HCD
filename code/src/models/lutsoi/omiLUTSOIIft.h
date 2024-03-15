/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiLUTSOIIft.h
 *  Date        : 2020_0420
 *  Description : LUTSOI data structures
 */


#include "omiIft.h"


/* This macro gets omiLUTSOIWorkData offset of a field */
#define OMI_LUTSOI_WORK_DATA_OFFSET(_field_) OMI_WORK_DATA_OFFSET(omiLUTSOIWorkData, _field_)

/* This structure defines LUTSOI work data, which must be double */
/* Only the first field is assigned by simulators for node voltages */
/* and others are assigned by OMI libraries. */
typedef struct omiLUTSOIWorkData
{
  /* Node voltages assigned by simulators, must be 1st field */
  double V[OMI_LUTSOI_STD_NODE_SIZE_MAX];
} omiLUTSOIWorkData;


/* This structure defines LUTSOI instance specific data */
typedef struct omiLUTSOISpecData
{
  /* LUTSOI node number */
  int node[OMI_LUTSOI_STD_NODE_SIZE_MAX];
  /* LUTSOI node map */
  int map [OMI_LUTSOI_STD_NODE_SIZE_MAX];

} omiLUTSOISpecData;

int omiLUTSOINoise (void *pModelData, void *pInstData, omiEvalData *pEvalData);


/* end of $RCSfile: omiLUTSOIIft.h,v $ */
