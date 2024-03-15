/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4.c
 *  Date        : 2010_1123
 *  Description : BSIM4 main function
 */


#include "omiBSIM4Def.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiBSIM4Update (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiBSIM4Model BSIM4Model;
  static omiBSIM4Instance BSIM4Inst;
  omiBSIM4Model *pBSIM4Model = &BSIM4Model;
  omiBSIM4Instance *pBSIM4Inst = &BSIM4Inst;


  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiBSIM4BuildCoreDataParam ();
    pModel->modelSize_o=B4_CORE_DATA_SIZE;
    pModel->param_o=omi_b4_core_data_param;
    return OMI_OK;
  }

  /* pCKT->evalType=2 for non-bsim4 instance regrouped parameters register */
  if(pCKT->evalType==2)
  {
    omiRegroupParamReg(pInstance);
    /* update random number */
    if(pModel->modelSize > 0 && pModel->pModelData)
    {
      pBSIM4Model = (omiBSIM4Model *) pModel->pModelData;
      omiBSIM4AssignModelParam (pModel, pBSIM4Model);
    }
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = B4_MOD_SIZE_o;
  pModel->param_o = omi_b4_mod_param_o;
  pModel->value_o = omi_b4_mod_value_o;
  pModel->bin = omi_b4_mod_bin;
  pInstance->instSize_o = B4_INST_SIZE_o;
  pInstance->param_o = omi_b4_inst_param_o;
  pInstance->value_o = omi_b4_inst_value_o;

  /* binary tree */
  omiBSIM4BuildInstParam ();
  omiBSIM4BuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pBSIM4Model;
    pModel->modelDataSize = sizeof(omiBSIM4Model);

    omiBSIM4InitModelParam (pBSIM4Model);
    omiBSIM4AssignModelParam (pModel, pBSIM4Model);
    omiBSIM4SetModelParamDefault (pBSIM4Model);
    omiBSIM4PrintModel (pModel, pBSIM4Model);
  }
  else
  {
    pBSIM4Model = (omiBSIM4Model *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pBSIM4Inst;
    pInstance->instDataSize = sizeof(omiBSIM4Instance);

    omiBSIM4InitInstParam (pBSIM4Inst);
    omiBSIM4AssignInstParam (pInstance, pBSIM4Inst);
    omiBSIM4SetInstParamDefault (pCKT, pBSIM4Model, pBSIM4Inst);
  }
  else
  {
    pBSIM4Inst = (omiBSIM4Instance *) pInstance->pInstData;
  }

  /* customized equations */
  pBSIM4Inst->instName = pInstance->instName;

  if(pBSIM4Model->modelType == NMOS) /* decide agemod and ageratio */
  {
    pBSIM4Model->agemod=1;
    pBSIM4Model->fvth0_age=1;
  }
  else
  {
    pBSIM4Model->agemod=2;		  
    pBSIM4Model->fvth0_age=-1;
  }		  

  if ((iret = omiBSIM4Temp (pCKT, pBSIM4Model, pBSIM4Inst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiBSIM4CheckModel (pInstance, pBSIM4Model, pBSIM4Inst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiBSIM4AssignInstParam (omiInstance *pInstance, omiBSIM4Instance *pBSIM4Inst)
{
  int i = 0;

  pBSIM4Inst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiBSIM4SetInstParam (pBSIM4Inst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiBSIM4AssignModelParam (omiModel *pModel, omiBSIM4Model *pBSIM4Model)
{
  int i = 0;

  pBSIM4Model->modelType = pModel->modelType;
  pBSIM4Model->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiBSIM4SetModelParam (pBSIM4Model, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4.c,v $ */


void omiRegroupParamReg (omiInstance *pInstance)
{
  static String inst_regroup_param_reg[omiInstRegroupParamSize]=
  {
    "misc_multi",
    "misc_scale",
    "extrinsic__dmcg",
    "extrinsic__dmci",
    "misc__xw",
    "misc__xl",
    "misc__delvto",
    "misc__mulu0",
    "flag_prnflag",
  };

  pInstance->instSize_o=omiInstRegroupParamSize;
  pInstance->param_o=inst_regroup_param_reg;

  return;
}

