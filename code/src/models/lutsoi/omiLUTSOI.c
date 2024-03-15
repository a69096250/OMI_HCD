/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiLUTSOI.c
 *  Date        : 2020_0420
 *  Description : LUTSOI main function
 */


#include "omiLUTSOIDef.h"

/* OMI regisiter parameter number */
#define omiInstRegroupParamSize 9

int omiLUTSOIUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  
  int iret=0;
  static omiLUTSOIModel LUTSOIModel;
  static omiLUTSOIInstance LUTSOIInst;
  omiLUTSOIModel *pLUTSOIModel = &LUTSOIModel;
  omiLUTSOIInstance *pLUTSOIInst = &LUTSOIInst;

  /* pModel->id==21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    omiLUTSOIBuildCoreDataParam ();
    pModel->modelSize_o=LSOI_CORE_DATA_SIZE;
    pModel->param_o=omi_lsoi_core_data_param;
    return OMI_OK;
  }

  /* set output */
  pModel->modelSize_o = LSOI_MOD_SIZE_o;
  pModel->param_o = omi_lsoi_mod_param_o;
  pModel->value_o = omi_lsoi_mod_value_o;
  pModel->bin = omi_lsoi_mod_bin;
  pInstance->instSize_o = LSOI_INST_SIZE_o;
  pInstance->param_o = omi_lsoi_inst_param_o;
  pInstance->value_o = omi_lsoi_inst_value_o;

  /* binary tree */
  omiLUTSOIBuildInstParam ();
  omiLUTSOIBuildModelParam ();

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pLUTSOIModel;
    pModel->modelDataSize = sizeof(omiLUTSOIModel);

    omiLUTSOIInitModelParam (pLUTSOIModel);
    omiLUTSOIAssignModelParam (pModel, pLUTSOIModel);
    omiLUTSOISetModelParamDefault (pLUTSOIModel);
    omiLUTSOIPrintModel (pModel, pLUTSOIModel);
  }
  else
  {
    pLUTSOIModel = (omiLUTSOIModel *) pModel->pModelData;
  }

  /* setup instance */
  if (pInstance->instSize > 0)
  {
    pInstance->pInstData = (void *) pLUTSOIInst;
    pInstance->instDataSize = sizeof(omiLUTSOIInstance);

    omiLUTSOIInitInstParam (pLUTSOIInst);
    omiLUTSOIAssignInstParam (pInstance, pLUTSOIInst);
    omiLUTSOISetInstParamDefault (pCKT, pLUTSOIModel, pLUTSOIInst);
  }
  else
  {
    pLUTSOIInst = (omiLUTSOIInstance *) pInstance->pInstData;
  }

  /* customized equations */
  pLUTSOIInst->instName = pInstance->instName;


  /*if(pLUTSOIModel->modelType == NMOS) /* decide agemod and ageratio 
  {
    pLUTSOIModel->agemod=1;
    pLUTSOIModel->fvth0_age=1;
  }
  else
  {
    pLUTSOIModel->agemod=2;		  
    pLUTSOIModel->fvth0_age=-1;
  }*/

  if ((iret = omiLUTSOITemp (pCKT, pLUTSOIModel, pLUTSOIInst)) == OMI_ERROR)
    return OMI_ERROR;
  if (omiLUTSOICheckModel (pInstance, pLUTSOIModel, pLUTSOIInst) == OMI_ERROR)
    return OMI_ERROR;

  return iret;
}


int omiLUTSOIAssignInstParam (omiInstance *pInstance, omiLUTSOIInstance *pLUTSOIInst)
{
  int i = 0;

  pLUTSOIInst->printWarn = pInstance->printWarn;

  for (i = 0; i < pInstance->instSize; i++)
  {
    omiLUTSOISetInstParam (pLUTSOIInst, pInstance->param[i], pInstance->value[i]);
  }

  return OMI_OK;
}


int omiLUTSOIAssignModelParam (omiModel *pModel, omiLUTSOIModel *pLUTSOIModel)
{
  int i = 0;

  pLUTSOIModel->modelType = pModel->modelType;
  pLUTSOIModel->printModel = pModel->printModel;

  for (i = 0; i < pModel->modelSize; i++)
  {
    omiLUTSOISetModelParam (pLUTSOIModel, pModel->param[i], pModel->value[i]);
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiLUTSOI.c,v $ */



