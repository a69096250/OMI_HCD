/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiMVSGIft.c
 *  Date        : 2019_0726
 *  Description : MVSG functions in IFT
 */


#include <math.h>
#include "omiMVSGDef.h"
#include "omiMVSGIft.h"




static int
omiMVSGInitdAge (omiMVSGModel *pMVSGModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiMVSGIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiMVSGModel *pMVSGModel = (omiMVSGModel *) pModelData;
  omiMVSGInstance *pMVSGInst = (omiMVSGInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pMVSGInst->pSimpleAge;
  omiMVSGCoreData *pMVSGCoreData = pEvalData->coreData;
  omiMVSGWorkData *pMVSGWorkData = (omiMVSGWorkData *) pEvalData->workData;
  omiMVSGSpecData *pMVSGSpecData = (omiMVSGSpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pMVSGSpecData->map;


  if (!pMVSGInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiMVSGInitdAge (pMVSGModel, pMVSGInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines MVSG IFT */
static omiIft omiMVSGIft =
{
/*omiMVSGUpdate*/
  sizeof(omiMVSGWorkData),
  sizeof(omiMVSGSpecData),
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
  omiMVSGIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiMVSGCreate (void *pModelData)
{
  omiMVSGModel *pMVSGModel = (omiMVSGModel *) pModelData;

  if (fabs(pMVSGModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pMVSGModel->omimod-1)<1e-3)
    return (char *)&omiMVSGIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pMVSGModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiMVSGIft.c,v $ */
