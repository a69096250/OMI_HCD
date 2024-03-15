/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiHiSIM2VATemp.c
 *  Date        : 2016_0718
 *  Description : To evaluate LOD/Mismatch equations,
 *                to update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiHiSIM2VADef.h"

extern omiModuleIft *pHiSIM2VAModuleIft;
extern double    *omi_hisim2va_mod_value_o;
extern omiSelectModelBin *omi_hisim2va_mod_bin;


int omiHiSIM2VATemp (omiCKT *pCKT, double *pHiSIM2VAModel)
{
  int i = 0;

  int iret = 0;
  omiModuleIft *pModuleIft = pHiSIM2VAModuleIft;

  /* update model parameters */
  for (i=0; i < HiSIM2VA_MOD_SIZE_o; i++) {
    iret=pModuleIft->modParamIndexOut[i];
    if (iret >= 0) {  /* Parameter Given */
      omi_hisim2va_mod_value_o[iret]=pHiSIM2VAModel[
          omiHiSIM2VAGetModelParamIdByName(pHiSIM2VAModuleIft->modParamName[i])];
    }
    else {
      omi_hisim2va_mod_value_o[iret] = OMI_AUNDEF;
    }
  }


  return OMI_OK;
}




/* end of $RCSfile: omiHiSIM2VATemp.c,v $ */
