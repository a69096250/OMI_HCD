/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMSOI.c
 *  Date        : 2019_0726
 *  Description : BSIMSOI main function
 */


#include "omiBSIMSOIDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiBSIMSOIUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiBSIMSOIModel BSIMSOIModel;
  static omiBSIMSOIInstance BSIMSOIInst;
  omiBSIMSOIModel *pBSIMSOIModel = &BSIMSOIModel;
  omiBSIMSOIInstance *pBSIMSOIInst = &BSIMSOIInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiBSIMSOIBuildCoreDataParam ();
    pModel->modelSize_o=BSOI_CORE_DATA_SIZE;
    pModel->param_o=omi_bsoi_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = BSOI_MOD_SIZE_o;
  pModel->param_o = omi_bsoi_mod_param_o;
  pModel->value_o = omi_bsoi_mod_value_o;
  pModel->bin = omi_bsoi_mod_bin;
  pInstance->instSize_o = BSOI_INST_SIZE_o;
  pInstance->param_o = omi_bsoi_inst_param_o;
  pInstance->value_o = omi_bsoi_inst_value_o;

  /* binary tree */
  omiBSIMSOIBuildInstParam ();
  omiBSIMSOIBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pBSIMSOIModel;
    pModel->modelDataSize = sizeof(omiBSIMSOIModel);

    omiBSIMSOIInitModelParam (pBSIMSOIModel);
    omiBSIMSOIAssignModelParam (pModel, pBSIMSOIModel);
    omiBSIMSOISetModelParamDefault (pBSIMSOIModel);
    omiBSIMSOIPrintModel (pModel, pBSIMSOIModel);
  }
  else
  {
    pBSIMSOIModel = (omiBSIMSOIModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pBSIMSOIInst;
    pInstance->instDataSize = sizeof(omiBSIMSOIInstance);

    omiBSIMSOIInitInstParam (pBSIMSOIInst);
    omiBSIMSOIAssignInstParam (pInstance, pBSIMSOIInst);
    omiBSIMSOISetInstParamDefault (pCKT, pBSIMSOIModel, pBSIMSOIInst);
  }
  else
  {
    pBSIMSOIInst = (omiBSIMSOIInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pBSIMSOIInst->instName = pInstance->instName;


  /*if(pBSIMSOIModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pBSIMSOIModel->agemod=1;
    pBSIMSOIModel->fvth0_age=1;
  }
  else
  {
    pBSIMSOIModel->agemod=2;		  
    pBSIMSOIModel->fvth0_age=-1;
  }*/

  if ((iret = omiBSIMSOITemp (pCKT, pBSIMSOIModel, pBSIMSOIInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiBSIMSOICheckModel (pInstance, pBSIMSOIModel, pBSIMSOIInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiBSIMSOIAssignInstParam (omiInstance *pInstance, omiBSIMSOIInstance *pBSIMSOIInst)
{
  int i = 0;

  pBSIMSOIInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiBSIMSOISetInstParam (pBSIMSOIInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiBSIMSOIAssignModelParam (omiModel *pModel, omiBSIMSOIModel *pBSIMSOIModel)
{
  int i = 0;

  pBSIMSOIModel->modelType = pModel->modelType;
  pBSIMSOIModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiBSIMSOISetModelParam (pBSIMSOIModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIMSOI.c,v $ */



