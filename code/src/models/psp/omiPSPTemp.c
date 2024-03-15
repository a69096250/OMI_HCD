/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiPSPTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiPSPDef.h"


static int omiPSPExtrapolateAge (omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst);
static int omiPSPDegradeAge (omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst);
extern void omiFreeElem (char *key, void *data);


int omiPSPTemp (omiCKT *pCKT, omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < PSP_INST_SIZE_o; i++)
    omi_psp_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < PSP_MOD_SIZE_o; i++)
    omi_psp_mod_value_o[i] = OMI_AUNDEF;


#include "omiPSPTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pPSPInst->instName = strdup (pPSPInst->instName);
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
      omiHashEnter (pHashTableAge, pPSPInst->instName, pSimpleAge);
      pPSPInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pPSPInst->pSimpleAge->modelNameId = OMI_MOS_PSP;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pPSPInst->instName);
      pPSPInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiPSPExtrapolateAge (pPSPModel, pPSPInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiPSPDegradeAge (pPSPModel, pPSPInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiPSPCheckModel (omiInstance *pInstance, omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst)
{
  return OMI_OK;
}

static
int omiPSPExtrapolateAge (omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pPSPInst->pSimpleAge;
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
int omiPSPDegradeAge (omiPSPModel *pPSPModel, omiPSPInstance *pPSPInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pPSPInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiPSPTemp.c,v $ */
