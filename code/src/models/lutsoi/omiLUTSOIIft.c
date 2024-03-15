/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiLUTSOIIft.c
 *  Date        : 2020_0420
 *  Description : LUTSOI functions in IFT
 */


#include <math.h>
#include "omiLUTSOIDef.h"
#include "omiLUTSOIIft.h"




static int
omiLUTSOIInitdAge (omiLUTSOIModel *pLUTSOIModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiLUTSOIIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiLUTSOIModel *pLUTSOIModel = (omiLUTSOIModel *) pModelData;
  omiLUTSOIInstance *pLUTSOIInst = (omiLUTSOIInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pLUTSOIInst->pSimpleAge;
  omiLUTSOICoreData *pLUTSOICoreData = pEvalData->coreData;
  omiLUTSOIWorkData *pLUTSOIWorkData = (omiLUTSOIWorkData *) pEvalData->workData;
  omiLUTSOISpecData *pLUTSOISpecData = (omiLUTSOISpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pLUTSOISpecData->map;


  if (!pLUTSOIInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiLUTSOIInitdAge (pLUTSOIModel, pLUTSOIInst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines LUTSOI IFT */
static omiIft omiLUTSOIIft =
{
/*omiLUTSOIUpdate*/
  sizeof(omiLUTSOIWorkData),
  sizeof(omiLUTSOISpecData),
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
  omiLUTSOIIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiLUTSOICreate (void *pModelData)
{
  omiLUTSOIModel *pLUTSOIModel = (omiLUTSOIModel *) pModelData;

  if (fabs(pLUTSOIModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pLUTSOIModel->omimod-1)<1e-3)
    return (char *)&omiLUTSOIIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pLUTSOIModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiLUTSOIIft.c,v $ */
