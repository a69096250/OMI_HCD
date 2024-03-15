/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiMVSG.c
 *  Date        : 2019_0726
 *  Description : MVSG main function
 */


#include "omiMVSGDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiMVSGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiMVSGModel MVSGModel;
  static omiMVSGInstance MVSGInst;
  omiMVSGModel *pMVSGModel = &MVSGModel;
  omiMVSGInstance *pMVSGInst = &MVSGInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiMVSGBuildCoreDataParam ();
    pModel->modelSize_o=MVSG_CORE_DATA_SIZE;
    pModel->param_o=omi_mvsg_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = MVSG_MOD_SIZE_o;
  pModel->param_o = omi_mvsg_mod_param_o;
  pModel->value_o = omi_mvsg_mod_value_o;
  pModel->bin = omi_mvsg_mod_bin;
  pInstance->instSize_o = MVSG_INST_SIZE_o;
  pInstance->param_o = omi_mvsg_inst_param_o;
  pInstance->value_o = omi_mvsg_inst_value_o;

  /* binary tree */
  omiMVSGBuildInstParam ();
  omiMVSGBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pMVSGModel;
    pModel->modelDataSize = sizeof(omiMVSGModel);

    omiMVSGInitModelParam (pMVSGModel);
    omiMVSGAssignModelParam (pModel, pMVSGModel);
    omiMVSGSetModelParamDefault (pMVSGModel);
    omiMVSGPrintModel (pModel, pMVSGModel);
  }
  else
  {
    pMVSGModel = (omiMVSGModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pMVSGInst;
    pInstance->instDataSize = sizeof(omiMVSGInstance);

    omiMVSGInitInstParam (pMVSGInst);
    omiMVSGAssignInstParam (pInstance, pMVSGInst);
    omiMVSGSetInstParamDefault (pCKT, pMVSGModel, pMVSGInst);
  }
  else
  {
    pMVSGInst = (omiMVSGInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pMVSGInst->instName = pInstance->instName;


  /*if(pMVSGModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pMVSGModel->agemod=1;
    pMVSGModel->fvth0_age=1;
  }
  else
  {
    pMVSGModel->agemod=2;		  
    pMVSGModel->fvth0_age=-1;
  }*/

  if ((iret = omiMVSGTemp (pCKT, pMVSGModel, pMVSGInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiMVSGCheckModel (pInstance, pMVSGModel, pMVSGInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiMVSGAssignInstParam (omiInstance *pInstance, omiMVSGInstance *pMVSGInst)
{
  int i = 0;

  pMVSGInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiMVSGSetInstParam (pMVSGInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiMVSGAssignModelParam (omiModel *pModel, omiMVSGModel *pMVSGModel)
{
  int i = 0;

  pMVSGModel->modelType = pModel->modelType;
  pMVSGModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiMVSGSetModelParam (pMVSGModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiMVSG.c,v $ */



