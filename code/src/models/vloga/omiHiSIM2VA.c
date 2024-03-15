/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiHiSIM2VA.c
 *  Date        : 2016_0718
 *  Description : HiSIM2VA main function
 */


#include "omiHiSIM2VADef.h"




static char  *omiHiSIM2VAmodParamName[HiSIM2VA_MOD_SIZE] =
  { "vfbc", "tox", "sita", "anox", "bnox", "dvg" };

static int omiHiSIM2VAmodParamDirection[HiSIM2VA_MOD_SIZE] =
  { 2, 2, 0, 0, 0, 0 };


static int omiHiSIM2VAmodParamIndexIn[HiSIM2VA_MOD_SIZE];
static int omiHiSIM2VAmodParamIndexOut[HiSIM2VA_MOD_SIZE];

static char  *omiHiSIM2VAcoreDataVarName[HiSIM2VA_CORE_SIZE] =
  { "Vgp", "Ps0" };

static int omiHiSIM2VAcoreDataVarIndex[HiSIM2VA_MOD_SIZE];

static omiModuleIft omiHiSIM2VAModuleIft =
{
  OMI_VLOGA,    /* modelID */
  0,            /* moduleID */
  "hisim2_va",  /* moduleName */
  HiSIM2VA_MOD_SIZE,   /* numModParam */
  omiHiSIM2VAmodParamName,
  omiHiSIM2VAmodParamDirection,
  omiHiSIM2VAmodParamIndexIn,
  omiHiSIM2VAmodParamIndexOut,
  0,            /* numInstParam */
  NULL,         /* instParamName */
  NULL,         /* instParamDirection */
  NULL,         /* instParamIndexIn */
  NULL,         /* instParamIndexOut */
  HiSIM2VA_CORE_SIZE,  /* numCoreDataVar */
  omiHiSIM2VAcoreDataVarName,
  omiHiSIM2VAcoreDataVarIndex
};

omiModuleIft *pHiSIM2VAModuleIft=&omiHiSIM2VAModuleIft;


char *omiHiSIM2VAInitializeModule(int model_id, int module_id, char *module_name)
{
  if (model_id==OMI_VLOGA && 
      !strcmp(module_name,omiHiSIM2VAModuleIft.moduleName)) {
    omiHiSIM2VAModuleIft.moduleID=module_id;
    return (char *)&omiHiSIM2VAModuleIft;
  }
  else {
    return NULL;
  }
}

static char hisim2va_mod_param_o[HiSIM2VA_MOD_SIZE_o][PARAM_LEN];
static double hisim2va_mod_value_o[HiSIM2VA_MOD_SIZE_o];
double *omi_hisim2va_mod_value_o=hisim2va_mod_value_o;
static omiSelectModelBin hisim2va_mod_bin;
omiSelectModelBin *omi_hisim2va_mod_bin=&hisim2va_mod_bin;


parNode *omiHiSIM2VAModelHeader = NULL;
ParamId omiHiSIM2VAGetModelParamIdByName (String aName)
{
  return omiGetNode(omiHiSIM2VAModelHeader, aName);
}


int omiHiSIM2VAUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  int i;
  int iret=0;
  static double omiHiSIM2VAModel[HiSIM2VA_MOD_SIZE];
  double *pHiSIM2VAModel = omiHiSIM2VAModel;
  omiModuleIft *pModuleIft = &omiHiSIM2VAModuleIft;

  /* set output */
  pModel->modelSize_o = HiSIM2VA_MOD_SIZE_o;
  pModel->param_o = (char**)hisim2va_mod_param_o;
  pModel->value_o = omi_hisim2va_mod_value_o;
  pModel->bin = &hisim2va_mod_bin;
  pInstance->instSize_o = HiSIM2VA_INST_SIZE_o;
  pInstance->param_o = NULL;
  pInstance->value_o = NULL;

  /* initialize binary tree */
  /* Formerly performed in BuilModelParam() and BuildInstParam() */
  if (omiHiSIM2VAModelHeader == NULL) {
    for (i=0; i < HiSIM2VA_MOD_SIZE; i++) {
      omiInsertNode(&omiHiSIM2VAModelHeader,
                    pModuleIft->modParamName[i],
                    i);
    }
  }

  /* setup model */
  if (pModel->modelSize > 0)
  {
    pModel->pModelData = (void *) pHiSIM2VAModel;
    pModel->modelDataSize = sizeof(omiHiSIM2VAModel);

    for (i=0; i < HiSIM2VA_MOD_SIZE; i++) {
      iret=pModuleIft->modParamIndexIn[i];
      if (iret >= 0) {  /* Parameter Given */
        pHiSIM2VAModel[i]=pModel->value[iret];
      }
      else  {   /* Assign Default */
        switch (i) {
	  case 0:   
            pHiSIM2VAModel[i]=0.2; /* vfbc */ 
            break;
	  case 1:
            pHiSIM2VAModel[i]=3e-9; /* tox */
            break;
	  case 2:
            pHiSIM2VAModel[i]=0.2; /* sita */
            break;
	  case 3:
            pHiSIM2VAModel[i]=0.7; /* anox */
            break;
	  case 4:
            pHiSIM2VAModel[i]=2.4e9; /* bnox */
            break;
	  case 5:
            pHiSIM2VAModel[i]=0.3; /* dvg */
            break;
	  default:
            break;
	}
      }
      if (pModuleIft->modParamDirection>0) {  /* Output parameter */
        iret=pModuleIft->modParamIndexOut[i];
        if (iret >= 0) {  /* Parameter Included in Output */
          pModel->param_o[iret]=omiHiSIM2VAmodParamName[i];
        }
      }
    }
    /* PrintModel - Skipping this for now */
  }
  else
  {
    pHiSIM2VAModel = (double *) pModel->pModelData;
  }


  /* customized equations */

  if ((iret = omiHiSIM2VATemp (pCKT, pHiSIM2VAModel)) == OMI_ERROR)
    return OMI_ERROR;

  /* check model - skipping this for now */

  return iret;
}


static int
omiHiSIM2VAInitdAge (double *pHiSIM2VAModel, omiHiSIM2Age *pHiSIM2Age)
{
  pHiSIM2Age->dAge = 0.0;
  pHiSIM2Age->tran_time = 0.0;
  pHiSIM2Age->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiHiSIM2VAIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  double *pHiSIM2VAModel = (double *) pModelData;

  return OMI_OK;
}


/* This structure defines HiSIM2VA IFT */
static omiIft omiHiSIM2VAIft =
{
  0,
  0,
  0,                                    /* probeDataSize */
  2,                                    /* noiseDataSize */
  NULL,
  NULL,                                 /* omiNoise */
  NULL,
  NULL,
  NULL,                                 /* omiTerminalType */
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  omiHiSIM2VAIntegrate,
};



  

/* This function returns the pointer of OMI IFT to simulator */
char *
omiHiSIM2VACreate (void *pModelData)
{
  return (char *)&omiHiSIM2VAIft;
}
 

/* This function tests the Veriog-A Interface, since there is no
   simulator at present that implements it. */
void omiHiSIM2VATest(void)
{
  int moduleID=1234;
  int iret;
  omiModuleIft *pIft;
  omiCKT CKT;
  omiModel Model;
  omiInstance Instance;
  double mod_value[2];

  pIft=(omiModuleIft*)omiHiSIM2VAInitializeModule(OMI_VLOGA,moduleID,"hisim2_va");
  if (!pIft) {
    omiPrint("ERROR: omiHiSIM2VATest: omiHiSIM2VAInitializeModule returned %d",
             pIft);
    return;
  }
  /* Code to model what the simulator would do after calling 
     omiInitializeModule() and before calling omiUpdate() */
  Model.value=mod_value;
  /* Set the input array to have two parameters, 
     one that is part of the output model (vfbc), and one that isn't (sita) */
  Model.value[0]=0.19;  /* sita */
  Model.value[1]=0.21;  /* vfbc */
  pIft->modParamIndexIn[0]=1; /* vfbc */ 
  pIft->modParamIndexIn[1]=-1; /* tox */
  pIft->modParamIndexIn[2]=0; /* sita */
  pIft->modParamIndexIn[3]=-1; /* anox */
  pIft->modParamIndexIn[4]=-1; /* bnox */
  pIft->modParamIndexIn[5]=-1; /* dvg */
  /* Set tox to be first output parameter, vfbc to be second */
  pIft->modParamIndexOut[0]=1; /* vfbc */ 
  pIft->modParamIndexOut[1]=0; /* tox */
  pIft->modParamIndexOut[2]=-1; /* sita */
  pIft->modParamIndexOut[3]=-1; /* anox */
  pIft->modParamIndexOut[4]=-1; /* bnox */
  pIft->modParamIndexOut[5]=-1; /* dvg */
  CKT.omiAge=1;  /* turn on Aging flow */
  iret=omiHiSIM2VAUpdate (&CKT, &Model, &Instance);
  if (iret != OMI_OK) {
    omiPrint("ERROR: omiHiSIM2VATest: omiHiSIM2VAUpdate returned %d (expected %d)",iret,OMI_OK);
    return;
  }
  /* Check to make sure that the BinTree structure was set correctly */
  omiPrint("INFO: omiHiSIM2VATest: bnox BinTree index is %d (expected %d)",omiHiSIM2VAGetModelParamIdByName("bnox"),4);
  omiPrint("INFO: omiHiSIM2VATest: dvg BinTree index is %d (expected %d)",omiHiSIM2VAGetModelParamIdByName("dvg"),5);
  /* Check to see that sita & anox in the input model were set correctly */
  omiPrint("INFO: omiHiSIM2VATest: pModelData[2] (sita) is %f (expected %f)",((double *)Model.pModelData)[2],0.19);
  omiPrint("INFO: omiHiSIM2VATest: pModelData[3] (anox) is %f (expected %f)",((double *)Model.pModelData)[3],0.7);
  /* Check to see that the param_o and value_o were set correctly */
  omiPrint("INFO: omiHiSIM2VATest: param_o[0] is %s (expected %s)",Model.param_o[0],"tox");
  omiPrint("INFO: omiHiSIM2VATest: param_o[1] is %s (expected %s)",Model.param_o[1],"vfbc");
  omiPrint("INFO: omiHiSIM2VATest: value_o[0] is %e (expected %e)",Model.value_o[0],3e-9);
  omiPrint("INFO: omiHiSIM2VATest: value_o[1] is %f (expected %f)",Model.value_o[1],0.21);

  return;
}
  
/* end of $RCSfile: omiHiSIM2VA.c,v $ */



