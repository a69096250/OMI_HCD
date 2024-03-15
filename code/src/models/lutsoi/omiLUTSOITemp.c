/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiLUTSOITemp.c
 *  Date        : 2020_0420
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiLUTSOIDef.h"


static int omiLUTSOIExtrapolateAge (omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst);
static int omiLUTSOIDegradeAge (omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst);
extern void omiFreeElem (char *key, void *data);


int omiLUTSOITemp (omiCKT *pCKT, omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < LSOI_INST_SIZE_o; i++)
    omi_lsoi_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < LSOI_MOD_SIZE_o; i++)
    omi_lsoi_mod_value_o[i] = OMI_AUNDEF;


#include "omiLUTSOITemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pLUTSOIInst->instName = strdup (pLUTSOIInst->instName);
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
      omiHashEnter (pHashTableAge, pLUTSOIInst->instName, pSimpleAge);
      pLUTSOIInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pLUTSOIInst->pSimpleAge->modelNameId = OMI_MOS_LUTSOI;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pLUTSOIInst->instName);
      pLUTSOIInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiLUTSOIExtrapolateAge (pLUTSOIModel, pLUTSOIInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiLUTSOIDegradeAge (pLUTSOIModel, pLUTSOIInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiLUTSOICheckModel (omiInstance *pInstance, omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst)
{
  return OMI_OK;
}

static
int omiLUTSOIExtrapolateAge (omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pLUTSOIInst->pSimpleAge;
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
int omiLUTSOIDegradeAge (omiLUTSOIModel *pLUTSOIModel, omiLUTSOIInstance *pLUTSOIInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pLUTSOIInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiLUTSOITemp.c,v $ */
