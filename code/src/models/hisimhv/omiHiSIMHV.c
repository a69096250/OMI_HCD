/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIMHV.c
 *  Date        : 2019_0726
 *  Description : HiSIMHV main function
 */


#include "omiHiSIMHVDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiHiSIMHVUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiHiSIMHVModel HiSIMHVModel;
  static omiHiSIMHVInstance HiSIMHVInst;
  omiHiSIMHVModel *pHiSIMHVModel = &HiSIMHVModel;
  omiHiSIMHVInstance *pHiSIMHVInst = &HiSIMHVInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiHiSIMHVBuildCoreDataParam ();
    pModel->modelSize_o=HSMHV_CORE_DATA_SIZE;
    pModel->param_o=omi_hsmhv_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = HSMHV_MOD_SIZE_o;
  pModel->param_o = omi_hsmhv_mod_param_o;
  pModel->value_o = omi_hsmhv_mod_value_o;
  pModel->bin = omi_hsmhv_mod_bin;
  pInstance->instSize_o = HSMHV_INST_SIZE_o;
  pInstance->param_o = omi_hsmhv_inst_param_o;
  pInstance->value_o = omi_hsmhv_inst_value_o;

  /* binary tree */
  omiHiSIMHVBuildInstParam ();
  omiHiSIMHVBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pHiSIMHVModel;
    pModel->modelDataSize = sizeof(omiHiSIMHVModel);

    omiHiSIMHVInitModelParam (pHiSIMHVModel);
    omiHiSIMHVAssignModelParam (pModel, pHiSIMHVModel);
    omiHiSIMHVSetModelParamDefault (pHiSIMHVModel);
    omiHiSIMHVPrintModel (pModel, pHiSIMHVModel);
  }
  else
  {
    pHiSIMHVModel = (omiHiSIMHVModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pHiSIMHVInst;
    pInstance->instDataSize = sizeof(omiHiSIMHVInstance);

    omiHiSIMHVInitInstParam (pHiSIMHVInst);
    omiHiSIMHVAssignInstParam (pInstance, pHiSIMHVInst);
    omiHiSIMHVSetInstParamDefault (pCKT, pHiSIMHVModel, pHiSIMHVInst);
  }
  else
  {
    pHiSIMHVInst = (omiHiSIMHVInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pHiSIMHVInst->instName = pInstance->instName;


  /*if(pHiSIMHVModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pHiSIMHVModel->agemod=1;
    pHiSIMHVModel->fvth0_age=1;
  }
  else
  {
    pHiSIMHVModel->agemod=2;		  
    pHiSIMHVModel->fvth0_age=-1;
  }*/

  if ((iret = omiHiSIMHVTemp (pCKT, pHiSIMHVModel, pHiSIMHVInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiHiSIMHVCheckModel (pInstance, pHiSIMHVModel, pHiSIMHVInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiHiSIMHVAssignInstParam (omiInstance *pInstance, omiHiSIMHVInstance *pHiSIMHVInst)
{
  int i = 0;

  pHiSIMHVInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiHiSIMHVSetInstParam (pHiSIMHVInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiHiSIMHVAssignModelParam (omiModel *pModel, omiHiSIMHVModel *pHiSIMHVModel)
{
  int i = 0;

  pHiSIMHVModel->modelType = pModel->modelType;
  pHiSIMHVModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiHiSIMHVSetModelParam (pHiSIMHVModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiHiSIMHV.c,v $ */



