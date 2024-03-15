/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiMVSGTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiMVSGDef.h"


static int omiMVSGExtrapolateAge (omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst);
static int omiMVSGDegradeAge (omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst);
extern void omiFreeElem (char *key, void *data);


int omiMVSGTemp (omiCKT *pCKT, omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < MVSG_INST_SIZE_o; i++)
    omi_mvsg_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < MVSG_MOD_SIZE_o; i++)
    omi_mvsg_mod_value_o[i] = OMI_AUNDEF;


#include "omiMVSGTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pMVSGInst->instName = strdup (pMVSGInst->instName);
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
      omiHashEnter (pHashTableAge, pMVSGInst->instName, pSimpleAge);
      pMVSGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pMVSGInst->pSimpleAge->modelNameId = OMI_MOS_MVSG;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pMVSGInst->instName);
      pMVSGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiMVSGExtrapolateAge (pMVSGModel, pMVSGInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiMVSGDegradeAge (pMVSGModel, pMVSGInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiMVSGCheckModel (omiInstance *pInstance, omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst)
{
  return OMI_OK;
}

static
int omiMVSGExtrapolateAge (omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pMVSGInst->pSimpleAge;
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
int omiMVSGDegradeAge (omiMVSGModel *pMVSGModel, omiMVSGInstance *pMVSGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pMVSGInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiMVSGTemp.c,v $ */
