/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMCMGTemp.c
 *  Date        : 2019_0726
 *  Date        : 2017-11-27
 *  Description : To update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiBSIMCMGDef.h"


static int omiBSIMCMGExtrapolateAge (omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst);
static int omiBSIMCMGDegradeAge (omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst);
extern void omiFreeElem (char *key, void *data);


int omiBSIMCMGTemp (omiCKT *pCKT, omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst)
{
  int i = 0;
  int iret = 0;
  double Tsimu = pCKT->CKTtemp;
  pBSIMCMGModel->tsimu = Tsimu;
  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < BCMG_INST_SIZE_o; i++)
    omi_bcmg_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < BCMG_MOD_SIZE_o; i++)
    omi_bcmg_mod_value_o[i] = OMI_AUNDEF;


#include "omiBSIMCMGTemp.inc"
 

  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pBSIMCMGInst->instName = strdup (pBSIMCMGInst->instName);
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
      omiHashEnter (pHashTableAge, pBSIMCMGInst->instName, pSimpleAge);
      pBSIMCMGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pBSIMCMGInst->pSimpleAge->modelNameId = OMI_MOS_BSIMCMG;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pBSIMCMGInst->instName);
      pBSIMCMGInst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiBSIMCMGExtrapolateAge (pBSIMCMGModel, pBSIMCMGInst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiBSIMCMGDegradeAge (pBSIMCMGModel, pBSIMCMGInst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiBSIMCMGCheckModel (omiInstance *pInstance, omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst)
{
  return OMI_OK;
}

static
int omiBSIMCMGExtrapolateAge (omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMCMGInst->pSimpleAge;
  double tran_time=0;
  double dVth_extra;
  tran_time = pSimpleAge->tran_time;  
  double T_tar = pBSIMCMGModel->dagetime;
  omiPrint("dagetime = %e",pBSIMCMGModel->dagetime);
  if(pSimpleAge->extrapolate_flag==0)
  {
    /* Insert Age Calculations Here */
    double AR_eff=0.0;
    double d0 = pBSIMCMGModel->d0;
    double nox = pBSIMCMGModel->nox;
    AR_eff = pSimpleAge->dVth/log(1+d0*pow(pSimpleAge->t_deg,nox));
    dVth_extra = AR_eff*log(1+d0*pow(T_tar,nox));
    pSimpleAge->dVth_extra=dVth_extra;
    omiPrint("dVth_ext=%e,AR=%e, part2=%e",pSimpleAge->dVth_extra,AR_eff,log(1+d0*pow(T_tar,nox)));
    omiPrint("1=%e,2=%e,3=%e",pSimpleAge->dVth,log(1+d0*pow(pSimpleAge->t_deg,nox)),pSimpleAge->t_deg);
  }    
  pSimpleAge->extrapolate_flag=1;
  return OMI_OK;
}

static
int omiBSIMCMGDegradeAge (omiBSIMCMGModel *pBSIMCMGModel, omiBSIMCMGInstance *pBSIMCMGInst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIMCMGInst->pSimpleAge;

  /* Insert Age Calculations Here */
  omiPrint("dVth_ext=%e",pSimpleAge->dVth_extra);
  omi_bcmg_mod_value_o[BCMG_MOD_dvtshift] = pSimpleAge->dVth_extra;
  return OMI_OK;
}


/* end of $RCSfile: omiBSIMCMGTemp.c,v $ */
