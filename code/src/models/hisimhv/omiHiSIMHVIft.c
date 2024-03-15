/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIMHVIft.c
 *  Date        : 2019_0726
 *  Description : HiSIMHV functions in IFT
 */


#include <math.h>
#include "omiHiSIMHVDef.h"
#include "omiHiSIMHVIft.h"




static int
omiHiSIMHVInitdAge (omiHiSIMHVModel *pHiSIMHVModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiHiSIMHVIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiHiSIMHVModel *pHiSIMHVModel = (omiHiSIMHVModel *) pModelData;
  omiHiSIMHVInstance *pHiSIMHVInst = (omiHiSIMHVInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pHiSIMHVInst->pSimpleAge;
  omiHiSIMHVCoreData *pHiSIMHVCoreData = pEvalData->coreData;
  omiHiSIMHVWorkData *pHiSIMHVWorkData = (omiHiSIMHVWorkData *) pEvalData->workData;
  omiHiSIMHVSpecData *pHiSIMHVSpecData = (omiHiSIMHVSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pHiSIMHVSpecData->map;


  if (!pHiSIMHVInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiHiSIMHVInitdAge (pHiSIMHVModel, pHiSIMHVInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines HiSIMHV IFT */
static omiIft omiHiSIMHVIft =
{
/*omiHiSIMHVUpdate*/
  sizeof(omiHiSIMHVWorkData),
  sizeof(omiHiSIMHVSpecData),
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
  omiHiSIMHVIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiHiSIMHVCreate (void *pModelData)
{
  omiHiSIMHVModel *pHiSIMHVModel = (omiHiSIMHVModel *) pModelData;

  if (fabs(pHiSIMHVModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pHiSIMHVModel->omimod-1)<1e-3)
    return (char *)&omiHiSIMHVIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pHiSIMHVModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiHiSIMHVIft.c,v $ */
