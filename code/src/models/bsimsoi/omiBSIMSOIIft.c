/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMSOIIft.c
 *  Date        : 2019_0726
 *  Description : BSIMSOI functions in IFT
 */


#include <math.h>
#include "omiBSIMSOIDef.h"
#include "omiBSIMSOIIft.h"




static int
omiBSIMSOIInitdAge (omiBSIMSOIModel *pBSIMSOIModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiBSIMSOIIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIMSOIModel *pBSIMSOIModel = (omiBSIMSOIModel *) pModelData;
  omiBSIMSOIInstance *pBSIMSOIInst = (omiBSIMSOIInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pBSIMSOIInst->pSimpleAge;
  omiBSIMSOICoreData *pBSIMSOICoreData = pEvalData->coreData;
  omiBSIMSOIWorkData *pBSIMSOIWorkData = (omiBSIMSOIWorkData *) pEvalData->workData;
  omiBSIMSOISpecData *pBSIMSOISpecData = (omiBSIMSOISpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pBSIMSOISpecData->map;


  if (!pBSIMSOIInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiBSIMSOIInitdAge (pBSIMSOIModel, pBSIMSOIInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines BSIMSOI IFT */
static omiIft omiBSIMSOIIft =
{
/*omiBSIMSOIUpdate*/
  sizeof(omiBSIMSOIWorkData),
  sizeof(omiBSIMSOISpecData),
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
  omiBSIMSOIIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiBSIMSOICreate (void *pModelData)
{
  omiBSIMSOIModel *pBSIMSOIModel = (omiBSIMSOIModel *) pModelData;

  if (fabs(pBSIMSOIModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pBSIMSOIModel->omimod-1)<1e-3)
    return (char *)&omiBSIMSOIIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pBSIMSOIModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiBSIMSOIIft.c,v $ */
