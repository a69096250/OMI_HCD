/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASMEval.c
 *  Date        : 2019_0726
 *  Description : ASM model evaluation
 */


#include <math.h>
#include "omiASMDef.h"
#include "omiASMIft.h"

#define sgn(A) (A>0 ? 1:( A<0 ? -1:0))



/* This is noise evaluation function */
int
omiASMNoise (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  /* Topology Modification not covered in this tutorial */  
  return OMI_OK;
}


/* end of $RCSfile: omiASMEval.c,v $ */
