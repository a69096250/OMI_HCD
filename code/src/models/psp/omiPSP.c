/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiPSP.c
 *  Date        : 2019_0726
 *  Description : PSP main function
 */


#include "omiPSPDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiPSPUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiPSPModel PSPModel;
  static omiPSPInstance PSPInst;
  omiPSPModel *pPSPModel = &PSPModel;
  omiPSPInstance *pPSPInst = &PSPInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiPSPBuildCoreDataParam ();
    pModel->modelSize_o=PSP_CORE_DATA_SIZE;
    pModel->param_o=omi_psp_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = PSP_MOD_SIZE_o;
  pModel->param_o = omi_psp_mod_param_o;
  pModel->value_o = omi_psp_mod_value_o;
  pModel->bin = omi_psp_mod_bin;
  pInstance->instSize_o = PSP_INST_SIZE_o;
  pInstance->param_o = omi_psp_inst_param_o;
  pInstance->value_o = omi_psp_inst_value_o;

  /* binary tree */
  omiPSPBuildInstParam ();
  omiPSPBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pPSPModel;
    pModel->modelDataSize = sizeof(omiPSPModel);

    omiPSPInitModelParam (pPSPModel);
    omiPSPAssignModelParam (pModel, pPSPModel);
    omiPSPSetModelParamDefault (pPSPModel);
    omiPSPPrintModel (pModel, pPSPModel);
  }
  else
  {
    pPSPModel = (omiPSPModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pPSPInst;
    pInstance->instDataSize = sizeof(omiPSPInstance);

    omiPSPInitInstParam (pPSPInst);
    omiPSPAssignInstParam (pInstance, pPSPInst);
    omiPSPSetInstParamDefault (pCKT, pPSPModel, pPSPInst);
  }
  else
  {
    pPSPInst = (omiPSPInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pPSPInst->instName = pInstance->instName;


  /*if(pPSPModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pPSPModel->agemod=1;
    pPSPModel->fvth0_age=1;
  }
  else
  {
    pPSPModel->agemod=2;		  
    pPSPModel->fvth0_age=-1;
  }*/

  if ((iret = omiPSPTemp (pCKT, pPSPModel, pPSPInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiPSPCheckModel (pInstance, pPSPModel, pPSPInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiPSPAssignInstParam (omiInstance *pInstance, omiPSPInstance *pPSPInst)
{
  int i = 0;

  pPSPInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiPSPSetInstParam (pPSPInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiPSPAssignModelParam (omiModel *pModel, omiPSPModel *pPSPModel)
{
  int i = 0;

  pPSPModel->modelType = pModel->modelType;
  pPSPModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiPSPSetModelParam (pPSPModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiPSP.c,v $ */



