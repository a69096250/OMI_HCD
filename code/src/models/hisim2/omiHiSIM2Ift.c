/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIM2Ift.c
 *  Date        : 2019_0726
 *  Description : HiSIM2 functions in IFT
 */


#include <math.h>
#include "omiHiSIM2Def.h"
#include "omiHiSIM2Ift.h"




static int
omiHiSIM2InitdAge (omiHiSIM2Model *pHiSIM2Model, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiHiSIM2Integrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiHiSIM2Model *pHiSIM2Model = (omiHiSIM2Model *) pModelData;
  omiHiSIM2Instance *pHiSIM2Inst = (omiHiSIM2Instance *) pInstData;

  omiSimpleAge *pSimpleAge = pHiSIM2Inst->pSimpleAge;
  omiHiSIM2CoreData *pHiSIM2CoreData = pEvalData->coreData;
  omiHiSIM2WorkData *pHiSIM2WorkData = (omiHiSIM2WorkData *) pEvalData->workData;
  omiHiSIM2SpecData *pHiSIM2SpecData = (omiHiSIM2SpecData *) pEvalData->specData;
  double step = pEvalData->step;
  int *map = pHiSIM2SpecData->map;


  if (!pHiSIM2Inst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiHiSIM2InitdAge (pHiSIM2Model, pHiSIM2Inst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines HiSIM2 IFT */
static omiIft omiHiSIM2Ift =
{
/*omiHiSIM2Update*/
  sizeof(omiHiSIM2WorkData),
  sizeof(omiHiSIM2SpecData),
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
  omiHiSIM2Integrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiHiSIM2Create (void *pModelData)
{
  omiHiSIM2Model *pHiSIM2Model = (omiHiSIM2Model *) pModelData;

  if (fabs(pHiSIM2Model->omimod)<1e-3)
    return NULL;
  else if (fabs(pHiSIM2Model->omimod-1)<1e-3)
    return (char *)&omiHiSIM2Ift;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pHiSIM2Model->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiHiSIM2Ift.c,v $ */
