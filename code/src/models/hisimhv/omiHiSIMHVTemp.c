/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIMHVTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiHiSIMHVDef.h"


static int omiHiSIMHVExtrapolateAge (omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst);
static int omiHiSIMHVDegradeAge (omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst);
extern void omiFreeElem (char *key, void *data);


int omiHiSIMHVTemp (omiCKT *pCKT, omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < HSMHV_INST_SIZE_o; i++)
    omi_hsmhv_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < HSMHV_MOD_SIZE_o; i++)
    omi_hsmhv_mod_value_o[i] = OMI_AUNDEF;


#include "omiHiSIMHVTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pHiSIMHVInst->instName = strdup (pHiSIMHVInst->instName);
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
      omiHashEnter (pHashTableAge, pHiSIMHVInst->instName, pSimpleAge);
      pHiSIMHVInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pHiSIMHVInst->pSimpleAge->modelNameId = OMI_MOS_HiSIMHV;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pHiSIMHVInst->instName);
      pHiSIMHVInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiHiSIMHVExtrapolateAge (pHiSIMHVModel, pHiSIMHVInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiHiSIMHVDegradeAge (pHiSIMHVModel, pHiSIMHVInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiHiSIMHVCheckModel (omiInstance *pInstance, omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst)
{
  return OMI_OK;
}

static
int omiHiSIMHVExtrapolateAge (omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pHiSIMHVInst->pSimpleAge;
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
int omiHiSIMHVDegradeAge (omiHiSIMHVModel *pHiSIMHVModel, omiHiSIMHVInstance *pHiSIMHVInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pHiSIMHVInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiHiSIMHVTemp.c,v $ */
