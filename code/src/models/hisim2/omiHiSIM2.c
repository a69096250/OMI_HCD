/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIM2.c
 *  Date        : 2019_0726
 *  Description : HiSIM2 main function
 */


#include "omiHiSIM2Def.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiHiSIM2Update (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiHiSIM2Model HiSIM2Model;
  static omiHiSIM2Instance HiSIM2Inst;
  omiHiSIM2Model *pHiSIM2Model = &HiSIM2Model;
  omiHiSIM2Instance *pHiSIM2Inst = &HiSIM2Inst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiHiSIM2BuildCoreDataParam ();
    pModel->modelSize_o=HSM2_CORE_DATA_SIZE;
    pModel->param_o=omi_hsm2_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = HSM2_MOD_SIZE_o;
  pModel->param_o = omi_hsm2_mod_param_o;
  pModel->value_o = omi_hsm2_mod_value_o;
  pModel->bin = omi_hsm2_mod_bin;
  pInstance->instSize_o = HSM2_INST_SIZE_o;
  pInstance->param_o = omi_hsm2_inst_param_o;
  pInstance->value_o = omi_hsm2_inst_value_o;

  /* binary tree */
  omiHiSIM2BuildInstParam ();
  omiHiSIM2BuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pHiSIM2Model;
    pModel->modelDataSize = sizeof(omiHiSIM2Model);

    omiHiSIM2InitModelParam (pHiSIM2Model);
    omiHiSIM2AssignModelParam (pModel, pHiSIM2Model);
    omiHiSIM2SetModelParamDefault (pHiSIM2Model);
    omiHiSIM2PrintModel (pModel, pHiSIM2Model);
  }
  else
  {
    pHiSIM2Model = (omiHiSIM2Model *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pHiSIM2Inst;
    pInstance->instDataSize = sizeof(omiHiSIM2Instance);

    omiHiSIM2InitInstParam (pHiSIM2Inst);
    omiHiSIM2AssignInstParam (pInstance, pHiSIM2Inst);
    omiHiSIM2SetInstParamDefault (pCKT, pHiSIM2Model, pHiSIM2Inst);
  }
  else
  {
    pHiSIM2Inst = (omiHiSIM2Instance *) pInstance->pInstData;
  }

  /* customized equations */
  pHiSIM2Inst->instName = pInstance->instName;


  /*if(pHiSIM2Model->modelType == NMOS) /* decide agemod and ageratio 
  {
    pHiSIM2Model->agemod=1;
    pHiSIM2Model->fvth0_age=1;
  }
  else
  {
    pHiSIM2Model->agemod=2;		  
    pHiSIM2Model->fvth0_age=-1;
  }*/

  if ((iret = omiHiSIM2Temp (pCKT, pHiSIM2Model, pHiSIM2Inst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiHiSIM2CheckModel (pInstance, pHiSIM2Model, pHiSIM2Inst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiHiSIM2AssignInstParam (omiInstance *pInstance, omiHiSIM2Instance *pHiSIM2Inst)
{
  int i = 0;

  pHiSIM2Inst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiHiSIM2SetInstParam (pHiSIM2Inst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiHiSIM2AssignModelParam (omiModel *pModel, omiHiSIM2Model *pHiSIM2Model)
{
  int i = 0;

  pHiSIM2Model->modelType = pModel->modelType;
  pHiSIM2Model->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiHiSIM2SetModelParam (pHiSIM2Model, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiHiSIM2.c,v $ */



