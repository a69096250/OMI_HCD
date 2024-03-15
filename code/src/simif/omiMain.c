/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiMain.c 
 *  Date        : 2016-11-22
 *  Description : OMI main function
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omiDef.h"
#include "omiIft.h"
#include "omiHash.h"


/* OMI regisiter parameter number */
#define omiModParamSize 177
#define omiInstParamSize 9
#define omiModBinSelParamSize 12
#define omiInstBinSelParamSize 5


pHashTable pHashTableAge = NULL;
double omiDagetime = 0.0;
char omiAgeInfoPath[512] = {'\0'};
int OMI_status = OMI_OK;
int omiGetCfgFlag = 0;
int omiFreeAgeFlag = 0;
int ModNameUpdate = 0;

/* OMI update function */
int (*omiPrint) (const char *fmt, ...) = printf;
static void omiParamReg (omiModel *pModel, omiInstance *pInstance);
static void omiBinSelParamReg (omiModel *pModel, omiInstance *pInstance);
extern int omiBSIM4Update (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiPSPUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiHiSIMHVUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiBSIMCMGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiHiSIM2Update (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiBSIMSOIUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiBSIMIMGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiBSIMBULKUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiASMUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiMVSGUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiLUTSOIUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
extern int omiHiSIM2VAUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);
omiModuleIft *pHiSIM2VAModuleIft;
extern char *omiHiSIM2VAInitializeModule(int model_id, int module_id, char *module_name);
extern void omiHiSIM2VATest(void);
void omiFreeElem (char *key, void *data);
static int omiReadAge (char *omiInput, char **instName, void **pAge);
int omiGetCfgInfo(omiCKT *pCKT );
int omiGetAgeInfo(omiCKT *pCKT );
int omiFindPath( char* input, char* output);

char *omiInitializeModule(int model_id, int module_id, char *module_name)
{
  if (model_id == OMI_VLOGA)
  {
    if (!strcmp(module_name,"hisim2_va"))
    {
      pHiSIM2VAModuleIft=(omiModuleIft*)omiHiSIM2VAInitializeModule(model_id,module_id,module_name);
      return (char*)pHiSIM2VAModuleIft;
    }
  }

  return NULL;
}

int omiUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  int iret=OMI_OK;
    static char omiOutputTemp[512]="\0";

  /* VLOGA Interface test inserted here, because no simulator supports
     this interface, currently.  */
  /* omiHiSIM2VATest(); */

  if (pCKT->print) omiPrint = pCKT->print;
  
  OMI_status=OMI_OK; /* set default value to OMI_OK */
  
  /*pModel->id=19 for bin selection parameters register*/
  if(pModel->id==19)
  {
    pModel->modelSize=0;
    pInstance->instSize=0;
    omiBinSelParamReg(pModel,pInstance);
    return OMI_OK;
  }
  /*pModel->id=20 for non-bsim4 parameters register*/
  if(pModel->id==20)
  {
    pModel->modelSize=0;
    pInstance->instSize=0;
    omiParamReg(pModel,pInstance);
    return OMI_OK;
  }
  /*pModel->id=21 indicates request for CoreData parameter list */
  if(pModel->id==21)
  {
    pModel->modelSize=0;
    pInstance->instSize=0;
    if (pModel->level == OMI_MOS_BSIM4)
      return omiBSIM4Update (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_PSP)
      return omiPSPUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_HiSIMHV)
      return omiHiSIMHVUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_BSIMCMG)
      return omiBSIMCMGUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_HiSIM2)
      return omiHiSIM2Update (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_BSIMSOI)
      return omiBSIMSOIUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_BSIMIMG)
      return omiBSIMIMGUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_BSIMBULK)
      return omiBSIMBULKUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_ASM)
      return omiASMUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_MVSG)
      return omiMVSGUpdate (pCKT, pModel, pInstance);
    if (pModel->level == OMI_MOS_LUTSOI)
      return omiLUTSOIUpdate (pCKT, pModel, pInstance);
    return OMI_OK;
  }

 /* parse omi configuration file */
  if ( omiGetCfgFlag == 0 ) strcpy(omiAgeInfoPath,"\0");
  if (pCKT->omiInput && (omiGetCfgFlag == 0)) /* open omi.cfg file once */
  {
    iret=omiGetCfgInfo( pCKT );
    if( iret == OMI_ERROR )
    {
      OMI_status = OMI_ERROR;    
      return   OMI_ERROR;
    }    
    omiGetCfgFlag = 1;
  }

  if( pCKT->omiAge == 1)
  {
    /* if omiSave==1 and current_alter's_omiInput != last_alter's_omiOutput, empty HashTable */
    if( pCKT->omiSave == 1 && omiFreeAgeFlag == 0 && pHashTableAge && pCKT->omiInput != NULL && strcmp(omiOutputTemp,pCKT->omiInput) != 0 )
    {
      omiFreeAge();
      omiGetCfgFlag = 0;
    }
    if(omiFreeAgeFlag == 0)
    {
      if(pCKT->omiOutput!=NULL)
        strcpy(omiOutputTemp,pCKT->omiOutput);
      else
        strcpy(omiOutputTemp,"\0");
    }
    omiFreeAgeFlag= 1;

    /* read back age history */
    if (strlen(omiAgeInfoPath) && !pHashTableAge && pCKT->evalType == evalTypeOther)
    {
      iret = omiGetAgeInfo( pCKT );
      if( iret == OMI_ERROR )
      {
        OMI_status = OMI_ERROR;    
        return   OMI_ERROR;
      }    
    }
  }
  

  /* enter model routines */
  if (pModel->id == OMI_MOS_BSIM4)
    return omiBSIM4Update (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_PSP)
    return omiPSPUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_HiSIMHV)
    return omiHiSIMHVUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_BSIMCMG)
    return omiBSIMCMGUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_HiSIM2)
    return omiHiSIM2Update (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_BSIMSOI)
    return omiBSIMSOIUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_BSIMIMG)
    return omiBSIMIMGUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_BSIMBULK)
    return omiBSIMBULKUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_ASM)
    return omiASMUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_MVSG)
    return omiMVSGUpdate (pCKT, pModel, pInstance);
  if (pModel->id == OMI_MOS_LUTSOI)
    return omiLUTSOIUpdate (pCKT, pModel, pInstance);

  if (pModel->id == OMI_VLOGA)
  {
    if (pModel->modelType == pHiSIM2VAModuleIft->moduleID)
      {
        return omiHiSIM2VAUpdate (pCKT, pModel, pInstance);
      }
  }
  
  return OMI_OK;
}


/* end of $RCSfile: omiMain.c,v $ */

/* OMI register function */
static
void omiParamReg (omiModel *pModel, omiInstance *pInstance)
{
  static String inst_param_reg[omiInstParamSize]=
  {
    "multi","scale","_dmcg","_dmci","_xw","_xl","_delvto","_mulu0","prnflag",
  };

  static String mod_param_reg[omiModParamSize]=
  {
    "omimodel",
    "tox_c","tox_g","tox_max","tox_min",
    "dxl_c","dxl_g","dxl_max","dxl_min",
    "dxw_c","dxw_g","dxw_max","dxw_min",
    "dvth_c","dvth_g","dvth_max","dvth_min",
    "dlvth_c","dlvth_g","dlvth_max","dlvth_min",
    "dwvth_c","dwvth_g","dwvth_max","dwvth_min",
    "dpvth_c","dpvth_g","dpvth_max","dpvth_min",
    "du0_c","du0_g","du0_max","du0_min",
    "dlu0_c","dlu0_g","dlu0_max","dlu0_min",
    "dwu0_c","dwu0_g","dwu0_max","dwu0_min",
    "dpu0_c","dpu0_g","dpu0_max","dpu0_min",
    "dvsat_c","dvsat_g","dvsat_max","dvsat_min",
    "dlvsat_c","dlvsat_g","dlvsat_max","dlvsat_min",
    "dwvsat_c","dwvsat_g","dwvsat_max","dwvsat_min",
    "dpvsat_c","dpvsat_g","dpvsat_max","dpvsat_min",
    "delvto","mulu0","mis_a_1","mis_a_2","parl1","parl2",
    "saref0","sbref0","wlod0","llod0","ku00","lku00","wku00","pku00","tku00",
    "llodku00","wlodku00","kvsat0","kvth00","lkvth00","wkvth00","pkvth00","llodvth0","wlodvth0","stk20",
    "lodk20","steta00","lodeta00","rn0xb","_tcj","_tcjsw","_tcjswg","_tpb","_tpbsw","_tpbswg",
    "_xtis","_njs","_xjbvs","_bvs","_mjs","_mjsws","_mjswgs","_jss","_jsws","_jswgs",
    "_jtss","_jtssws","_jtsswgs","_njts","_njtssw","_njtsswg","_njtsdx","_njtsswdx","_njtsswgdx","_tnjts",
    "_tnjtssw","_tnjtsswg","_vtss","_vtssws","_vtsswgs","_xtss","_xtssws","_xtsswgs","_pbs","_pbsws",
    "_pbswgs","_cjs","_cjsws","_cjswgs","_xtid","_njd","_xjbvd","_bvd","_mjd","_mjswd",
    "_mjswgd","_jsd","_jswd","_jswgd","_jtsd","_jtsswd","_jtsswgd","_njtsd","_njtsswd","_njtsswgd",
    "_tnjtsd","_tnjtsswd","_tnjtsswgd","_vtsd","_vtsswd","_vtsswgd","_xtsd","_xtsswd","_xtsswgd","_pbd",
    "_pbswd","_pbswgd","_cjd","_cjswd","_cjswgd","_dwj","_wlc","_wln","_wwc","_wwn",
    "_wwlc","omimod","agemod","dagetime","fvth0_age","n_age","Hs_age","ms_age","Hg_age","mg_age","Vgsdmax",
  };

  pInstance->instSize_o=omiInstParamSize;
  pInstance->param_o=inst_param_reg;
  pModel->modelSize_o=omiModParamSize;
  pModel->param_o=mod_param_reg;

}

static
void omiBinSelParamReg (omiModel *pModel, omiInstance *pInstance)
{
  static String mod_binselparam_reg[omiModBinSelParamSize]=
  {
    "dxl_c","dxl_g","dxl_max","dxl_min",
    "dxw_c","dxw_g","dxw_max","dxw_min",
    "mis_a_1","mis_a_2","parl1","parl2",
  };
  static String inst_binselparam_reg[omiInstBinSelParamSize]=
  {
    "w","l","nf","multi","scale",
  };
  pInstance->instSize_o=omiInstBinSelParamSize;
  pInstance->param_o=inst_binselparam_reg;
  pModel->modelSize_o=omiModBinSelParamSize;
  pModel->param_o=mod_binselparam_reg;
}


void omiFreeElem (char *key, void *data)
{
  free (key);
  key = NULL;

  free (data);
  data = NULL;
}


static
int omiReadAge (char *omiInput, char **instName, void **pAge)
{
  static FILE *omiAgeFile = NULL;
  int len = 0;
  int nmemb=1;

  if (! omiAgeFile)
  {
    if ((omiAgeFile = fopen (omiInput, "rb")) == NULL)
    {
      omiPrint("\n  **error** OMI cannot open %s", omiInput);
      OMI_status=OMI_ERROR;
      return -1;
    }
  }

  if (!feof(omiAgeFile))
  {
    len = getw (omiAgeFile);
    if (len <= 0 )
    {
      fclose (omiAgeFile);
      omiAgeFile = NULL;
      return 0;
    }
    *instName = (char *) malloc (len+1);
    nmemb = fread (*instName, len, 1, omiAgeFile); /* return 0 if wrong format */
    (*instName)[len] = '\0';
    len = getw (omiAgeFile);
    *pAge = (void *) malloc (len);
    fread (*pAge, len, 1, omiAgeFile);
    if( nmemb==0 )
    {
      omiPrint("\n  **error** omiInput file format error");
      OMI_status=OMI_ERROR;
      return -1;
    }
    else return 1;
  }
  else
  {
    fclose (omiAgeFile);
    omiAgeFile = NULL;
    return 0;
  }
}

int omiGetCfgInfo(omiCKT *pCKT )
{
  static FILE *omiInputFile = NULL;
  char line1[512],data[2][512];
  int length,data_switch;
  char path_name[512];
      
  if ((omiInputFile = fopen (pCKT->omiInput, "r")) == NULL)
  {
    omiPrint("\n  **error** OMI cannot open %s", pCKT->omiInput);
    OMI_status=OMI_ERROR;
    return OMI_ERROR;
  }

  strcpy(omiAgeInfoPath,"wrong_omi_age_setting");
  while( fgets(line1, sizeof(line1), omiInputFile)!=NULL)
  {
    sscanf(line1,"%s %d %s",data[0],&data_switch,data[1]);
    if( strncmp(data[0],"*",1)==0 ) continue;
    if( strncasecmp(data[0],"age_data_file",13)==0 )
    {      
      if( data_switch==-1 )
        strcpy(omiAgeInfoPath,"\0");
      else if( data_switch==0 ) /* relative path */
      {
        omiFindPath( pCKT->omiInput, path_name);
        length=strlen(data[1]);
        if( data[1][length-1]=='\n' ) data[1][length-1]=data[1][length];
        strcpy(omiAgeInfoPath,path_name);
        strcat(omiAgeInfoPath,data[1]);
      }
      else /* full path */
      {
        length=strlen(data[1]);
        if( data[1][length-1]=='\n' ) data[1][length-1]=data[1][length];
        strcpy(omiAgeInfoPath,data[1]);
      }
    }
    if( strncasecmp(data[0],"age_model_file",14)==0 )
      continue;
    if( strncasecmp(data[0],"age_setting_file",16)==0 )
      continue;
  }
  fclose(omiInputFile);
  return OMI_OK;
}
    
int omiGetAgeInfo(omiCKT *pCKT )
{
  int i=0;
  char *instName = NULL;
  void *pAge = NULL;
  int check_format=1;

  if (pCKT->tblSize == 0)
    i = 128 * 2048;    /* default */
  else
    i = pCKT->tblSize;

  pHashTableAge = omiHashCreate (i, omiFreeElem);

  while (check_format = omiReadAge (omiAgeInfoPath, &instName, &pAge))
  {
    if(check_format==-1)  
    {
      OMI_status = OMI_ERROR;
      return OMI_ERROR;
    }
    omiHashEnter (pHashTableAge, instName, pAge);
  }
  
  return OMI_OK;
}

int omiFindPath( char* input, char* output)
{
  int i=0;
  int location=0;
  char temp[512];
  
  strcpy( temp, input );
  while( (unsigned)i < strlen(temp) )
  {
    if( temp[i]=='/' || temp[i]=='\\' )
      location=i;
    i++;
  }
  strncpy(output,temp,location+1);
  output[location+1]='\0';
  
  return 0;
}

