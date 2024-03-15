/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASM.c
 *  Date        : 2019_0726
 *  Description : ASM main function
 */


#include "omiASMDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiASMUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiASMModel ASMModel;
  static omiASMInstance ASMInst;
  omiASMModel *pASMModel = &ASMModel;
  omiASMInstance *pASMInst = &ASMInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiASMBuildCoreDataParam ();
    pModel->modelSize_o=ASM_CORE_DATA_SIZE;
    pModel->param_o=omi_asm_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = ASM_MOD_SIZE_o;
  pModel->param_o = omi_asm_mod_param_o;
  pModel->value_o = omi_asm_mod_value_o;
  pModel->bin = omi_asm_mod_bin;
  pInstance->instSize_o = ASM_INST_SIZE_o;
  pInstance->param_o = omi_asm_inst_param_o;
  pInstance->value_o = omi_asm_inst_value_o;

  /* binary tree */
  omiASMBuildInstParam ();
  omiASMBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pASMModel;
    pModel->modelDataSize = sizeof(omiASMModel);

    omiASMInitModelParam (pASMModel);
    omiASMAssignModelParam (pModel, pASMModel);
    omiASMSetModelParamDefault (pASMModel);
    omiASMPrintModel (pModel, pASMModel);
  }
  else
  {
    pASMModel = (omiASMModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pASMInst;
    pInstance->instDataSize = sizeof(omiASMInstance);

    omiASMInitInstParam (pASMInst);
    omiASMAssignInstParam (pInstance, pASMInst);
    omiASMSetInstParamDefault (pCKT, pASMModel, pASMInst);
  }
  else
  {
    pASMInst = (omiASMInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pASMInst->instName = pInstance->instName;


  /*if(pASMModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pASMModel->agemod=1;
    pASMModel->fvth0_age=1;
  }
  else
  {
    pASMModel->agemod=2;		  
    pASMModel->fvth0_age=-1;
  }*/

  if ((iret = omiASMTemp (pCKT, pASMModel, pASMInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiASMCheckModel (pInstance, pASMModel, pASMInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiASMAssignInstParam (omiInstance *pInstance, omiASMInstance *pASMInst)
{
  int i = 0;

  pASMInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiASMSetInstParam (pASMInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiASMAssignModelParam (omiModel *pModel, omiASMModel *pASMModel)
{
  int i = 0;

  pASMModel->modelType = pModel->modelType;
  pASMModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiASMSetModelParam (pASMModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiASM.c,v $ */



