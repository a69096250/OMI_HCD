/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMIMG.c
 *  Date        : 2019_0726
 *  Description : BSIMIMG main function
 */


#include "omiBSIMIMGDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiBSIMIMGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiBSIMIMGModel BSIMIMGModel;
  static omiBSIMIMGInstance BSIMIMGInst;
  omiBSIMIMGModel *pBSIMIMGModel = &BSIMIMGModel;
  omiBSIMIMGInstance *pBSIMIMGInst = &BSIMIMGInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiBSIMIMGBuildCoreDataParam ();
    pModel->modelSize_o=BIMG_CORE_DATA_SIZE;
    pModel->param_o=omi_bimg_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = BIMG_MOD_SIZE_o;
  pModel->param_o = omi_bimg_mod_param_o;
  pModel->value_o = omi_bimg_mod_value_o;
  pModel->bin = omi_bimg_mod_bin;
  pInstance->instSize_o = BIMG_INST_SIZE_o;
  pInstance->param_o = omi_bimg_inst_param_o;
  pInstance->value_o = omi_bimg_inst_value_o;

  /* binary tree */
  omiBSIMIMGBuildInstParam ();
  omiBSIMIMGBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pBSIMIMGModel;
    pModel->modelDataSize = sizeof(omiBSIMIMGModel);

    omiBSIMIMGInitModelParam (pBSIMIMGModel);
    omiBSIMIMGAssignModelParam (pModel, pBSIMIMGModel);
    omiBSIMIMGSetModelParamDefault (pBSIMIMGModel);
    omiBSIMIMGPrintModel (pModel, pBSIMIMGModel);
  }
  else
  {
    pBSIMIMGModel = (omiBSIMIMGModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pBSIMIMGInst;
    pInstance->instDataSize = sizeof(omiBSIMIMGInstance);

    omiBSIMIMGInitInstParam (pBSIMIMGInst);
    omiBSIMIMGAssignInstParam (pInstance, pBSIMIMGInst);
    omiBSIMIMGSetInstParamDefault (pCKT, pBSIMIMGModel, pBSIMIMGInst);
  }
  else
  {
    pBSIMIMGInst = (omiBSIMIMGInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pBSIMIMGInst->instName = pInstance->instName;


  /*if(pBSIMIMGModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pBSIMIMGModel->agemod=1;
    pBSIMIMGModel->fvth0_age=1;
  }
  else
  {
    pBSIMIMGModel->agemod=2;		  
    pBSIMIMGModel->fvth0_age=-1;
  }*/

  if ((iret = omiBSIMIMGTemp (pCKT, pBSIMIMGModel, pBSIMIMGInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiBSIMIMGCheckModel (pInstance, pBSIMIMGModel, pBSIMIMGInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiBSIMIMGAssignInstParam (omiInstance *pInstance, omiBSIMIMGInstance *pBSIMIMGInst)
{
  int i = 0;

  pBSIMIMGInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiBSIMIMGSetInstParam (pBSIMIMGInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiBSIMIMGAssignModelParam (omiModel *pModel, omiBSIMIMGModel *pBSIMIMGModel)
{
  int i = 0;

  pBSIMIMGModel->modelType = pModel->modelType;
  pBSIMIMGModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiBSIMIMGSetModelParam (pBSIMIMGModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIMIMG.c,v $ */



