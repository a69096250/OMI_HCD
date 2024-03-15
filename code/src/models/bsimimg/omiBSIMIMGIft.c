/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMIMGIft.c
 *  Date        : 2019_0726
 *  Description : BSIMIMG functions in IFT
 */


#include <math.h>
#include "omiBSIMIMGDef.h"
#include "omiBSIMIMGIft.h"




static int
omiBSIMIMGInitdAge (omiBSIMIMGModel *pBSIMIMGModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiBSIMIMGIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIMIMGModel *pBSIMIMGModel = (omiBSIMIMGModel *) pModelData;
  omiBSIMIMGInstance *pBSIMIMGInst = (omiBSIMIMGInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pBSIMIMGInst->pSimpleAge;
  omiBSIMIMGCoreData *pBSIMIMGCoreData = pEvalData->coreData;
  omiBSIMIMGWorkData *pBSIMIMGWorkData = (omiBSIMIMGWorkData *) pEvalData->workData;
  omiBSIMIMGSpecData *pBSIMIMGSpecData = (omiBSIMIMGSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pBSIMIMGSpecData->map;


  if (!pBSIMIMGInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiBSIMIMGInitdAge (pBSIMIMGModel, pBSIMIMGInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines BSIMIMG IFT */
static omiIft omiBSIMIMGIft =
{
/*omiBSIMIMGUpdate*/
  sizeof(omiBSIMIMGWorkData),
  sizeof(omiBSIMIMGSpecData),
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
  omiBSIMIMGIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiBSIMIMGCreate (void *pModelData)
{
  omiBSIMIMGModel *pBSIMIMGModel = (omiBSIMIMGModel *) pModelData;

  if (fabs(pBSIMIMGModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pBSIMIMGModel->omimod-1)<1e-3)
    return (char *)&omiBSIMIMGIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pBSIMIMGModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiBSIMIMGIft.c,v $ */
