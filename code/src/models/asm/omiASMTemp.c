/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASMTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiASMDef.h"


static int omiASMExtrapolateAge (omiASMModel *pASMModel, omiASMInstance *pASMInst);
static int omiASMDegradeAge (omiASMModel *pASMModel, omiASMInstance *pASMInst);
extern void omiFreeElem (char *key, void *data);


int omiASMTemp (omiCKT *pCKT, omiASMModel *pASMModel, omiASMInstance *pASMInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < ASM_INST_SIZE_o; i++)
    omi_asm_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < ASM_MOD_SIZE_o; i++)
    omi_asm_mod_value_o[i] = OMI_AUNDEF;


#include "omiASMTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pASMInst->instName = strdup (pASMInst->instName);
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
      omiHashEnter (pHashTableAge, pASMInst->instName, pSimpleAge);
      pASMInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pASMInst->pSimpleAge->modelNameId = OMI_MOS_ASM;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pASMInst->instName);
      pASMInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiASMExtrapolateAge (pASMModel, pASMInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiASMDegradeAge (pASMModel, pASMInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiASMCheckModel (omiInstance *pInstance, omiASMModel *pASMModel, omiASMInstance *pASMInst)
{
  return OMI_OK;
}

static
int omiASMExtrapolateAge (omiASMModel *pASMModel, omiASMInstance *pASMInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pASMInst->pSimpleAge;
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
int omiASMDegradeAge (omiASMModel *pASMModel, omiASMInstance *pASMInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pASMInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiASMTemp.c,v $ */
