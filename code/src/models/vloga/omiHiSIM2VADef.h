/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiHiSIM2VADef.h
 *  Date        : 2016_0629
 *  Description : VerilogA HiSIM2 data structures
 */


#include "omiDef.h"
#include "omiIft.h"
#include "omiBinTree.h"
#include "omiHash.h"
#include "omiAge.h"


#define pwr(A, B) ((A) >= 0 ? pow(fabs(A), B) : (-1 * pow(fabs(A),B)))
#define min(A, B) ((A) > (B) ? (B) : (A))
#define max(A, B) ((A) > (B) ? (A) : (B))
#define abs(A)     ((A) >= 0 ? (A) : -(A))

#define TRUE 1
#define PARAM_LEN 16

#define HiSIM2VA_CORE_SIZE 2


/* Instance parameter */
#define HiSIM2VA_INST_SIZE 0     /* number of instance parameter (total) */
#define HiSIM2VA_INST_SIZE_o  0  /* number of instance parameter (output) */
#define HiSIM2VA_INST_l              0


/* Model parameter */
#define HiSIM2VA_MOD_SIZE 6 /* number of model parameter (total) */
#define HiSIM2VA_MOD_SIZE_o  2  /* number of model parameter (output) */




ParamId omiHiSIM2VAGetModelParamIdByName (String aName);
int    omiHiSIM2VATemp (omiCKT *pCKT, double *pHiSIM2VAModel);

  
/* end of $RCSfile: omiHiSIM2VADef.h,v $ */
