/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiPSPIft.c
 *  Date        : 2019_0726
 *  Description : PSP functions in IFT
 */


#include <math.h>
#include "omiPSPDef.h"
#include "omiPSPIft.h"




static int
omiPSPInitdAge (omiPSPModel *pPSPModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiPSPIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiPSPModel *pPSPModel = (omiPSPModel *) pModelData;
  omiPSPInstance *pPSPInst = (omiPSPInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pPSPInst->pSimpleAge;
  omiPSPCoreData *pPSPCoreData = pEvalData->coreData;
  omiPSPWorkData *pPSPWorkData = (omiPSPWorkData *) pEvalData->workData;
  omiPSPSpecData *pPSPSpecData = (omiPSPSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pPSPSpecData->map;


  if (!pPSPInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiPSPInitdAge (pPSPModel, pPSPInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines PSP IFT */
static omiIft omiPSPIft =
{
/*omiPSPUpdate*/
  sizeof(omiPSPWorkData),
  sizeof(omiPSPSpecData),
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
  omiPSPIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiPSPCreate (void *pModelData)
{
  omiPSPModel *pPSPModel = (omiPSPModel *) pModelData;

  if (fabs(pPSPModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pPSPModel->omimod-1)<1e-3)
    return (char *)&omiPSPIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pPSPModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiPSPIft.c,v $ */
