/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMBULKTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiBSIMBULKDef.h"


static int omiBSIMBULKExtrapolateAge (omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst);
static int omiBSIMBULKDegradeAge (omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst);
extern void omiFreeElem (char *key, void *data);


int omiBSIMBULKTemp (omiCKT *pCKT, omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < BBK_INST_SIZE_o; i++)
    omi_bbk_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < BBK_MOD_SIZE_o; i++)
    omi_bbk_mod_value_o[i] = OMI_AUNDEF;


#include "omiBSIMBULKTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pBSIMBULKInst->instName = strdup (pBSIMBULKInst->instName);
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
      omiHashEnter (pHashTableAge, pBSIMBULKInst->instName, pSimpleAge);
      pBSIMBULKInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pBSIMBULKInst->pSimpleAge->modelNameId = OMI_MOS_BSIMBULK;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pBSIMBULKInst->instName);
      pBSIMBULKInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiBSIMBULKExtrapolateAge (pBSIMBULKModel, pBSIMBULKInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiBSIMBULKDegradeAge (pBSIMBULKModel, pBSIMBULKInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiBSIMBULKCheckModel (omiInstance *pInstance, omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst)
{
  return OMI_OK;
}

static
int omiBSIMBULKExtrapolateAge (omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMBULKInst->pSimpleAge;
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
int omiBSIMBULKDegradeAge (omiBSIMBULKModel *pBSIMBULKModel, omiBSIMBULKInstance *pBSIMBULKInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMBULKInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiBSIMBULKTemp.c,v $ */
