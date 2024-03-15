/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMBULK.c
 *  Date        : 2019_0726
 *  Description : BSIMBULK main function
 */


#include "omiBSIMBULKDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiBSIMBULKUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiBSIMBULKModel BSIMBULKModel;
  static omiBSIMBULKInstance BSIMBULKInst;
  omiBSIMBULKModel *pBSIMBULKModel = &BSIMBULKModel;
  omiBSIMBULKInstance *pBSIMBULKInst = &BSIMBULKInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiBSIMBULKBuildCoreDataParam ();
    pModel->modelSize_o=BBK_CORE_DATA_SIZE;
    pModel->param_o=omi_bbk_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = BBK_MOD_SIZE_o;
  pModel->param_o = omi_bbk_mod_param_o;
  pModel->value_o = omi_bbk_mod_value_o;
  pModel->bin = omi_bbk_mod_bin;
  pInstance->instSize_o = BBK_INST_SIZE_o;
  pInstance->param_o = omi_bbk_inst_param_o;
  pInstance->value_o = omi_bbk_inst_value_o;

  /* binary tree */
  omiBSIMBULKBuildInstParam ();
  omiBSIMBULKBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pBSIMBULKModel;
    pModel->modelDataSize = sizeof(omiBSIMBULKModel);

    omiBSIMBULKInitModelParam (pBSIMBULKModel);
    omiBSIMBULKAssignModelParam (pModel, pBSIMBULKModel);
    omiBSIMBULKSetModelParamDefault (pBSIMBULKModel);
    omiBSIMBULKPrintModel (pModel, pBSIMBULKModel);
  }
  else
  {
    pBSIMBULKModel = (omiBSIMBULKModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pBSIMBULKInst;
    pInstance->instDataSize = sizeof(omiBSIMBULKInstance);

    omiBSIMBULKInitInstParam (pBSIMBULKInst);
    omiBSIMBULKAssignInstParam (pInstance, pBSIMBULKInst);
    omiBSIMBULKSetInstParamDefault (pCKT, pBSIMBULKModel, pBSIMBULKInst);
  }
  else
  {
    pBSIMBULKInst = (omiBSIMBULKInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pBSIMBULKInst->instName = pInstance->instName;


  /*if(pBSIMBULKModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pBSIMBULKModel->agemod=1;
    pBSIMBULKModel->fvth0_age=1;
  }
  else
  {
    pBSIMBULKModel->agemod=2;		  
    pBSIMBULKModel->fvth0_age=-1;
  }*/

  if ((iret = omiBSIMBULKTemp (pCKT, pBSIMBULKModel, pBSIMBULKInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiBSIMBULKCheckModel (pInstance, pBSIMBULKModel, pBSIMBULKInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiBSIMBULKAssignInstParam (omiInstance *pInstance, omiBSIMBULKInstance *pBSIMBULKInst)
{
  int i = 0;

  pBSIMBULKInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiBSIMBULKSetInstParam (pBSIMBULKInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiBSIMBULKAssignModelParam (omiModel *pModel, omiBSIMBULKModel *pBSIMBULKModel)
{
  int i = 0;

  pBSIMBULKModel->modelType = pModel->modelType;
  pBSIMBULKModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiBSIMBULKSetModelParam (pBSIMBULKModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIMBULK.c,v $ */



