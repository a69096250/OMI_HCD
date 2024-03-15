/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMBULKIft.c
 *  Date        : 2019_0726
 *  Description : BSIMBULK functions in IFT
 */


#include <math.h>
#include "omiBSIMBULKDef.h"
#include "omiBSIMBULKIft.h"




static int
omiBSIMBULKInitdAge (omiBSIMBULKModel *pBSIMBULKModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiBSIMBULKIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIMBULKModel *pBSIMBULKModel = (omiBSIMBULKModel *) pModelData;
  omiBSIMBULKInstance *pBSIMBULKInst = (omiBSIMBULKInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pBSIMBULKInst->pSimpleAge;
  omiBSIMBULKCoreData *pBSIMBULKCoreData = pEvalData->coreData;
  omiBSIMBULKWorkData *pBSIMBULKWorkData = (omiBSIMBULKWorkData *) pEvalData->workData;
  omiBSIMBULKSpecData *pBSIMBULKSpecData = (omiBSIMBULKSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pBSIMBULKSpecData->map;


  if (!pBSIMBULKInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiBSIMBULKInitdAge (pBSIMBULKModel, pBSIMBULKInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines BSIMBULK IFT */
static omiIft omiBSIMBULKIft =
{
/*omiBSIMBULKUpdate*/
  sizeof(omiBSIMBULKWorkData),
  sizeof(omiBSIMBULKSpecData),
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
  omiBSIMBULKIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiBSIMBULKCreate (void *pModelData)
{
  omiBSIMBULKModel *pBSIMBULKModel = (omiBSIMBULKModel *) pModelData;

  if (fabs(pBSIMBULKModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pBSIMBULKModel->omimod-1)<1e-3)
    return (char *)&omiBSIMBULKIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pBSIMBULKModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiBSIMBULKIft.c,v $ */
