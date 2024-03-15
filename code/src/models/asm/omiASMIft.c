/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASMIft.c
 *  Date        : 2019_0726
 *  Description : ASM functions in IFT
 */


#include <math.h>
#include "omiASMDef.h"
#include "omiASMIft.h"




static int
omiASMInitdAge (omiASMModel *pASMModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiASMIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiASMModel *pASMModel = (omiASMModel *) pModelData;
  omiASMInstance *pASMInst = (omiASMInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pASMInst->pSimpleAge;
  omiASMCoreData *pASMCoreData = pEvalData->coreData;
  omiASMWorkData *pASMWorkData = (omiASMWorkData *) pEvalData->workData;
  omiASMSpecData *pASMSpecData = (omiASMSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pASMSpecData->map;


  if (!pASMInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiASMInitdAge (pASMModel, pASMInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines ASM IFT */
static omiIft omiASMIft =
{
/*omiASMUpdate*/
  sizeof(omiASMWorkData),
  sizeof(omiASMSpecData),
  0,                                    /* probeDataSize */
  2,                                    /* noiseDataSize */
  NULL,
  NULL,                                 /* omiNoise */
  NULL,
  NULL,
  NULL,                                 /* omiTerminalType */
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  omiASMIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiASMCreate (void *pModelData)
{
  omiASMModel *pASMModel = (omiASMModel *) pModelData;

  if (fabs(pASMModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pASMModel->omimod-1)<1e-3)
    return (char *)&omiASMIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pASMModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiASMIft.c,v $ */
