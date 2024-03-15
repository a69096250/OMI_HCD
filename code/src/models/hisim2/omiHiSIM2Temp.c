/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIM2Temp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiHiSIM2Def.h"


static int omiHiSIM2ExtrapolateAge (omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst);
static int omiHiSIM2DegradeAge (omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst);
extern void omiFreeElem (char *key, void *data);


int omiHiSIM2Temp (omiCKT *pCKT, omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < HSM2_INST_SIZE_o; i++)
    omi_hsm2_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < HSM2_MOD_SIZE_o; i++)
    omi_hsm2_mod_value_o[i] = OMI_AUNDEF;


#include "omiHiSIM2Temp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pHiSIM2Inst->instName = strdup (pHiSIM2Inst->instName);
      pSimpleAge = (void *) malloc (sizeof(omiSimpleAge));

      memset (pSimpleAge, 0, sizeof(omiSimpleAge));
      if (! pHashTableAge)
      {
        if (pCKT->tblSize == 0)
          i = 128 * 2048;    /* default */
        else
          i = pCKT->tblSize;

        pHashTableAge = omiHashCreate(i, omiFreeElem);
      }
      omiHashEnter (pHashTableAge, pHiSIM2Inst->instName, pSimpleAge);
      pHiSIM2Inst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pHiSIM2Inst->pSimpleAge->modelNameId = OMI_MOS_HiSIM2;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pHiSIM2Inst->instName);
      pHiSIM2Inst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiHiSIM2ExtrapolateAge (pHiSIM2Model, pHiSIM2Inst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiHiSIM2DegradeAge (pHiSIM2Model, pHiSIM2Inst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiHiSIM2CheckModel (omiInstance *pInstance, omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst)
{
  return OMI_OK;
}

static
int omiHiSIM2ExtrapolateAge (omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pHiSIM2Inst->pSimpleAge;
  double tran_time=0;

  tran_time = pSimpleAge->tran_time;  
  if(pSimpleAge->extrapolate_flag==0)
  {
    /* Insert Age Calculations Here */

  }    
  pSimpleAge->extrapolate_flag=1;
  return OMI_OK;
}

static
int omiHiSIM2DegradeAge (omiHiSIM2Model *pHiSIM2Model, omiHiSIM2Instance *pHiSIM2Inst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pHiSIM2Inst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiHiSIM2Temp.c,v $ */
