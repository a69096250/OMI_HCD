/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMIMGTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiBSIMIMGDef.h"


static int omiBSIMIMGExtrapolateAge (omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst);
static int omiBSIMIMGDegradeAge (omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst);
extern void omiFreeElem (char *key, void *data);


int omiBSIMIMGTemp (omiCKT *pCKT, omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst)
{
  int i = 0;
  int iret = 0;


  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < BIMG_INST_SIZE_o; i++)
    omi_bimg_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < BIMG_MOD_SIZE_o; i++)
    omi_bimg_mod_value_o[i] = OMI_AUNDEF;


#include "omiBSIMIMGTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pBSIMIMGInst->instName = strdup (pBSIMIMGInst->instName);
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
      omiHashEnter (pHashTableAge, pBSIMIMGInst->instName, pSimpleAge);
      pBSIMIMGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pBSIMIMGInst->pSimpleAge->modelNameId = OMI_MOS_BSIMIMG;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pBSIMIMGInst->instName);
      pBSIMIMGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiBSIMIMGExtrapolateAge (pBSIMIMGModel, pBSIMIMGInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiBSIMIMGDegradeAge (pBSIMIMGModel, pBSIMIMGInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiBSIMIMGCheckModel (omiInstance *pInstance, omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst)
{
  return OMI_OK;
}

static
int omiBSIMIMGExtrapolateAge (omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMIMGInst->pSimpleAge;
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
int omiBSIMIMGDegradeAge (omiBSIMIMGModel *pBSIMIMGModel, omiBSIMIMGInstance *pBSIMIMGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMIMGInst->pSimpleAge;

  /* Insert Age Calculations Here */
  return OMI_OK;
}


/* end of $RCSfile: omiBSIMIMGTemp.c,v $ */
