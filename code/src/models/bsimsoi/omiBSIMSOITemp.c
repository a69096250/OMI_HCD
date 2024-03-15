/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMSOITemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiBSIMSOIDef.h"


static int omiBSIMSOIExtrapolateAge (omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst);
static int omiBSIMSOIDegradeAge (omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst);
extern void omiFreeElem (char *key, void *data);


int omiBSIMSOITemp (omiCKT *pCKT, omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < BSOI_INST_SIZE_o; i++)
    omi_bsoi_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < BSOI_MOD_SIZE_o; i++)
    omi_bsoi_mod_value_o[i] = OMI_AUNDEF;


#include "omiBSIMSOITemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pBSIMSOIInst->instName = strdup (pBSIMSOIInst->instName);
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
      omiHashEnter (pHashTableAge, pBSIMSOIInst->instName, pSimpleAge);
      pBSIMSOIInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pBSIMSOIInst->pSimpleAge->modelNameId = OMI_MOS_BSIMSOI;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pBSIMSOIInst->instName);
      pBSIMSOIInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiBSIMSOIExtrapolateAge (pBSIMSOIModel, pBSIMSOIInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiBSIMSOIDegradeAge (pBSIMSOIModel, pBSIMSOIInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiBSIMSOICheckModel (omiInstance *pInstance, omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst)
{
  return OMI_OK;
}

static
int omiBSIMSOIExtrapolateAge (omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMSOIInst->pSimpleAge;
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
int omiBSIMSOIDegradeAge (omiBSIMSOIModel *pBSIMSOIModel, omiBSIMSOIInstance *pBSIMSOIInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMSOIInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiBSIMSOITemp.c,v $ */
