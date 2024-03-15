/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMCMG.c
 *  Date        : 2019_0726
 *  Description : BSIMCMG main function
 */


#include "omiBSIMCMGDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiBSIMCMGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiBSIMCMGModel BSIMCMGModel;
  static omiBSIMCMGInstance BSIMCMGInst;
  omiBSIMCMGModel *pBSIMCMGModel = &BSIMCMGModel;
  omiBSIMCMGInstance *pBSIMCMGInst = &BSIMCMGInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiBSIMCMGBuildCoreDataParam ();
    pModel->modelSize_o=BCMG_CORE_DATA_SIZE;
    pModel->param_o=omi_bcmg_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = BCMG_MOD_SIZE_o;
  pModel->param_o = omi_bcmg_mod_param_o;
  pModel->value_o = omi_bcmg_mod_value_o;
  pModel->bin = omi_bcmg_mod_bin;
  pInstance->instSize_o = BCMG_INST_SIZE_o;
  pInstance->param_o = omi_bcmg_inst_param_o;
  pInstance->value_o = omi_bcmg_inst_value_o;

  /* binary tree */
  omiBSIMCMGBuildInstParam ();
  omiBSIMCMGBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pBSIMCMGModel;
    pModel->modelDataSize = sizeof(omiBSIMCMGModel);

    omiBSIMCMGInitModelParam (pBSIMCMGModel);
    omiBSIMCMGAssignModelParam (pModel, pBSIMCMGModel);
    omiBSIMCMGSetModelParamDefault (pBSIMCMGModel);
    omiBSIMCMGPrintModel (pModel, pBSIMCMGModel);
  }
  else
  {
    pBSIMCMGModel = (omiBSIMCMGModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pBSIMCMGInst;
    pInstance->instDataSize = sizeof(omiBSIMCMGInstance);

    omiBSIMCMGInitInstParam (pBSIMCMGInst);
    omiBSIMCMGAssignInstParam (pInstance, pBSIMCMGInst);
    omiBSIMCMGSetInstParamDefault (pCKT, pBSIMCMGModel, pBSIMCMGInst);
  }
  else
  {
    pBSIMCMGInst = (omiBSIMCMGInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pBSIMCMGInst->instName = pInstance->instName;


  /*if(pBSIMCMGModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pBSIMCMGModel->agemod=1;
    pBSIMCMGModel->fvth0_age=1;
  }
  else
  {
    pBSIMCMGModel->agemod=2;		  
    pBSIMCMGModel->fvth0_age=-1;
  }*/

  if ((iret = omiBSIMCMGTemp (pCKT, pBSIMCMGModel, pBSIMCMGInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiBSIMCMGCheckModel (pInstance, pBSIMCMGModel, pBSIMCMGInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiBSIMCMGAssignInstParam (omiInstance *pInstance, omiBSIMCMGInstance *pBSIMCMGInst)
{
  int i = 0;

  pBSIMCMGInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiBSIMCMGSetInstParam (pBSIMCMGInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiBSIMCMGAssignModelParam (omiModel *pModel, omiBSIMCMGModel *pBSIMCMGModel)
{
  int i = 0;

  pBSIMCMGModel->modelType = pModel->modelType;
  pBSIMCMGModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiBSIMCMGSetModelParam (pBSIMCMGModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIMCMG.c,v $ */



