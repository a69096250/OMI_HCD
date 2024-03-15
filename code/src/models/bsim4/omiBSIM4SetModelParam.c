/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4SetModelParam.c
 *  Date        : 2010_1123
 *  Description : To get model parameter values
 */


#include "omiBSIM4Def.h"


int omiBSIM4SetModelParam (omiBSIM4Model *pBSIM4Model, String aName, double aValue)
{
  extern int ModNameUpdate;

  switch(omiBSIM4GetModelParamIdByName(aName))
  {
    case B4_MOD_tox_c:
      pBSIM4Model->tox_c = aValue;
      pBSIM4Model->tox_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_tox_g:
      pBSIM4Model->tox_g = aValue;
      pBSIM4Model->tox_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_tox_max:
      pBSIM4Model->tox_max = aValue;
      pBSIM4Model->tox_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_tox_min:
      pBSIM4Model->tox_min = aValue;
      pBSIM4Model->tox_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxl_c:
      pBSIM4Model->dxl_c = aValue;
      pBSIM4Model->dxl_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxl_g:
      pBSIM4Model->dxl_g = aValue;
      pBSIM4Model->dxl_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxl_max:
      pBSIM4Model->dxl_max = aValue;
      pBSIM4Model->dxl_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxl_min:
      pBSIM4Model->dxl_min = aValue;
      pBSIM4Model->dxl_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxw_c:
      pBSIM4Model->dxw_c = aValue;
      pBSIM4Model->dxw_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxw_g:
      pBSIM4Model->dxw_g = aValue;
      pBSIM4Model->dxw_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxw_max:
      pBSIM4Model->dxw_max = aValue;
      pBSIM4Model->dxw_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dxw_min:
      pBSIM4Model->dxw_min = aValue;
      pBSIM4Model->dxw_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvth_c:
      pBSIM4Model->dvth_c = aValue;
      pBSIM4Model->dvth_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvth_g:
      pBSIM4Model->dvth_g = aValue;
      pBSIM4Model->dvth_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvth_max:
      pBSIM4Model->dvth_max = aValue;
      pBSIM4Model->dvth_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvth_min:
      pBSIM4Model->dvth_min = aValue;
      pBSIM4Model->dvth_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvth_c:
      pBSIM4Model->dlvth_c = aValue;
      pBSIM4Model->dlvth_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvth_g:
      pBSIM4Model->dlvth_g = aValue;
      pBSIM4Model->dlvth_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvth_max:
      pBSIM4Model->dlvth_max = aValue;
      pBSIM4Model->dlvth_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvth_min:
      pBSIM4Model->dlvth_min = aValue;
      pBSIM4Model->dlvth_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvth_c:
      pBSIM4Model->dwvth_c = aValue;
      pBSIM4Model->dwvth_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvth_g:
      pBSIM4Model->dwvth_g = aValue;
      pBSIM4Model->dwvth_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvth_max:
      pBSIM4Model->dwvth_max = aValue;
      pBSIM4Model->dwvth_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvth_min:
      pBSIM4Model->dwvth_min = aValue;
      pBSIM4Model->dwvth_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvth_c:
      pBSIM4Model->dpvth_c = aValue;
      pBSIM4Model->dpvth_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvth_g:
      pBSIM4Model->dpvth_g = aValue;
      pBSIM4Model->dpvth_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvth_max:
      pBSIM4Model->dpvth_max = aValue;
      pBSIM4Model->dpvth_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvth_min:
      pBSIM4Model->dpvth_min = aValue;
      pBSIM4Model->dpvth_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_du0_c:
      pBSIM4Model->du0_c = aValue;
      pBSIM4Model->du0_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_du0_g:
      pBSIM4Model->du0_g = aValue;
      pBSIM4Model->du0_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_du0_max:
      pBSIM4Model->du0_max = aValue;
      pBSIM4Model->du0_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_du0_min:
      pBSIM4Model->du0_min = aValue;
      pBSIM4Model->du0_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlu0_c:
      pBSIM4Model->dlu0_c = aValue;
      pBSIM4Model->dlu0_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlu0_g:
      pBSIM4Model->dlu0_g = aValue;
      pBSIM4Model->dlu0_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlu0_max:
      pBSIM4Model->dlu0_max = aValue;
      pBSIM4Model->dlu0_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlu0_min:
      pBSIM4Model->dlu0_min = aValue;
      pBSIM4Model->dlu0_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwu0_c:
      pBSIM4Model->dwu0_c = aValue;
      pBSIM4Model->dwu0_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwu0_g:
      pBSIM4Model->dwu0_g = aValue;
      pBSIM4Model->dwu0_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwu0_max:
      pBSIM4Model->dwu0_max = aValue;
      pBSIM4Model->dwu0_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwu0_min:
      pBSIM4Model->dwu0_min = aValue;
      pBSIM4Model->dwu0_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpu0_c:
      pBSIM4Model->dpu0_c = aValue;
      pBSIM4Model->dpu0_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpu0_g:
      pBSIM4Model->dpu0_g = aValue;
      pBSIM4Model->dpu0_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpu0_max:
      pBSIM4Model->dpu0_max = aValue;
      pBSIM4Model->dpu0_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpu0_min:
      pBSIM4Model->dpu0_min = aValue;
      pBSIM4Model->dpu0_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvsat_c:
      pBSIM4Model->dvsat_c = aValue;
      pBSIM4Model->dvsat_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvsat_g:
      pBSIM4Model->dvsat_g = aValue;
      pBSIM4Model->dvsat_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvsat_max:
      pBSIM4Model->dvsat_max = aValue;
      pBSIM4Model->dvsat_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dvsat_min:
      pBSIM4Model->dvsat_min = aValue;
      pBSIM4Model->dvsat_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvsat_c:
      pBSIM4Model->dlvsat_c = aValue;
      pBSIM4Model->dlvsat_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvsat_g:
      pBSIM4Model->dlvsat_g = aValue;
      pBSIM4Model->dlvsat_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvsat_max:
      pBSIM4Model->dlvsat_max = aValue;
      pBSIM4Model->dlvsat_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dlvsat_min:
      pBSIM4Model->dlvsat_min = aValue;
      pBSIM4Model->dlvsat_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvsat_c:
      pBSIM4Model->dwvsat_c = aValue;
      pBSIM4Model->dwvsat_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvsat_g:
      pBSIM4Model->dwvsat_g = aValue;
      pBSIM4Model->dwvsat_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvsat_max:
      pBSIM4Model->dwvsat_max = aValue;
      pBSIM4Model->dwvsat_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dwvsat_min:
      pBSIM4Model->dwvsat_min = aValue;
      pBSIM4Model->dwvsat_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvsat_c:
      pBSIM4Model->dpvsat_c = aValue;
      pBSIM4Model->dpvsat_cGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvsat_g:
      pBSIM4Model->dpvsat_g = aValue;
      pBSIM4Model->dpvsat_gGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvsat_max:
      pBSIM4Model->dpvsat_max = aValue;
      pBSIM4Model->dpvsat_maxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dpvsat_min:
      pBSIM4Model->dpvsat_min = aValue;
      pBSIM4Model->dpvsat_minGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;


/***************************/
    case B4_MOD_delvto:
      pBSIM4Model->delvto = aValue;
      pBSIM4Model->delvtoGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_mulu0:
      pBSIM4Model->mulu0 = aValue;
      pBSIM4Model->mulu0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_mis_a_1:
      pBSIM4Model->mis_a_1 = aValue;
      pBSIM4Model->mis_a_1Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_mis_a_2:
      pBSIM4Model->mis_a_2 = aValue;
      pBSIM4Model->mis_a_2Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_parl1:
      pBSIM4Model->parl1 = aValue;
      pBSIM4Model->parl1Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_parl2:
      pBSIM4Model->parl2 = aValue;
      pBSIM4Model->parl2Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_saref0:
      pBSIM4Model->saref0 = aValue;
      pBSIM4Model->saref0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_sbref0:
      pBSIM4Model->sbref0 = aValue;
      pBSIM4Model->sbref0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_wlod0:
      pBSIM4Model->wlod0 = aValue;
      pBSIM4Model->wlod0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_ku00:
      pBSIM4Model->ku00 = aValue;
      pBSIM4Model->ku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_lku00:
      pBSIM4Model->lku00 = aValue;
      pBSIM4Model->lku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_wku00:
      pBSIM4Model->wku00 = aValue;
      pBSIM4Model->wku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_pku00:
      pBSIM4Model->pku00 = aValue;
      pBSIM4Model->pku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_tku00:
      pBSIM4Model->tku00 = aValue;
      pBSIM4Model->tku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_llodku00:
      pBSIM4Model->llodku00 = aValue;
      pBSIM4Model->llodku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_wlodku00:
      pBSIM4Model->wlodku00 = aValue;
      pBSIM4Model->wlodku00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_kvsat0:
      pBSIM4Model->kvsat0 = aValue;
      pBSIM4Model->kvsat0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_kvth00:
      pBSIM4Model->kvth00 = aValue;
      pBSIM4Model->kvth00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_lkvth00:
      pBSIM4Model->lkvth00 = aValue;
      pBSIM4Model->lkvth00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_wkvth00:
      pBSIM4Model->wkvth00 = aValue;
      pBSIM4Model->wkvth00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_pkvth00:
      pBSIM4Model->pkvth00 = aValue;
      pBSIM4Model->pkvth00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_llodvth0:
      pBSIM4Model->llodvth0 = aValue;
      pBSIM4Model->llodvth0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_wlodvth0:
      pBSIM4Model->wlodvth0 = aValue;
      pBSIM4Model->wlodvth0Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_stk20:
      pBSIM4Model->stk20 = aValue;
      pBSIM4Model->stk20Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_lodk20:
      pBSIM4Model->lodk20 = aValue;
      pBSIM4Model->lodk20Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_steta00:
      pBSIM4Model->steta00 = aValue;
      pBSIM4Model->steta00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_lodeta00:
      pBSIM4Model->lodeta00 = aValue;
      pBSIM4Model->lodeta00Given = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_rn0xb:
      pBSIM4Model->rn0xb = aValue;
      pBSIM4Model->rn0xbGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tcj:
      pBSIM4Model->_tcj = aValue;
      pBSIM4Model->_tcjGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tcjsw:
      pBSIM4Model->_tcjsw = aValue;
      pBSIM4Model->_tcjswGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tcjswg:
      pBSIM4Model->_tcjswg = aValue;
      pBSIM4Model->_tcjswgGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tpb:
      pBSIM4Model->_tpb = aValue;
      pBSIM4Model->_tpbGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tpbsw:
      pBSIM4Model->_tpbsw = aValue;
      pBSIM4Model->_tpbswGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tpbswg:
      pBSIM4Model->_tpbswg = aValue;
      pBSIM4Model->_tpbswgGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtis:
      pBSIM4Model->_xtis = aValue;
      pBSIM4Model->_xtisGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njs:
      pBSIM4Model->_njs = aValue;
      pBSIM4Model->_njsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__bvs:
      pBSIM4Model->_bvs = aValue;
      pBSIM4Model->_bvsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjs:
      pBSIM4Model->_mjs = aValue;
      pBSIM4Model->_mjsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjsws:
      pBSIM4Model->_mjsws = aValue;
      pBSIM4Model->_mjswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjswgs:
      pBSIM4Model->_mjswgs = aValue;
      pBSIM4Model->_mjswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jss:
      pBSIM4Model->_jss = aValue;
      pBSIM4Model->_jssGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jsws:
      pBSIM4Model->_jsws = aValue;
      pBSIM4Model->_jswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jswgs:
      pBSIM4Model->_jswgs = aValue;
      pBSIM4Model->_jswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtss:
      pBSIM4Model->_jtss = aValue;
      pBSIM4Model->_jtssGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtssws:
      pBSIM4Model->_jtssws = aValue;
      pBSIM4Model->_jtsswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtsswgs:
      pBSIM4Model->_jtsswgs = aValue;
      pBSIM4Model->_jtsswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njts:
      pBSIM4Model->_njts = aValue;
      pBSIM4Model->_njtsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njtssw:
      pBSIM4Model->_njtssw = aValue;
      pBSIM4Model->_njtsswGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njtsswg:
      pBSIM4Model->_njtsswg = aValue;
      pBSIM4Model->_njtsswgGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njtsdx:
      pBSIM4Model->_njtsdx = aValue;
      pBSIM4Model->_njtsdxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njtsswdx:
      pBSIM4Model->_njtsswdx = aValue;
      pBSIM4Model->_njtsswdxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njtsswgdx:
      pBSIM4Model->_njtsswgdx = aValue;
      pBSIM4Model->_njtsswgdxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjts:
      pBSIM4Model->_tnjts = aValue;
      pBSIM4Model->_tnjtsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjtssw:
      pBSIM4Model->_tnjtssw = aValue;
      pBSIM4Model->_tnjtsswGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjtsswg:
      pBSIM4Model->_tnjtsswg = aValue;
      pBSIM4Model->_tnjtsswgGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtss:
      pBSIM4Model->_vtss = aValue;
      pBSIM4Model->_vtssGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtssws:
      pBSIM4Model->_vtssws = aValue;
      pBSIM4Model->_vtsswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtsswgs:
      pBSIM4Model->_vtsswgs = aValue;
      pBSIM4Model->_vtsswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtss:
      pBSIM4Model->_xtss = aValue;
      pBSIM4Model->_xtssGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtssws:
      pBSIM4Model->_xtssws = aValue;
      pBSIM4Model->_xtsswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtsswgs:
      pBSIM4Model->_xtsswgs = aValue;
      pBSIM4Model->_xtsswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbs:
      pBSIM4Model->_pbs = aValue;
      pBSIM4Model->_pbsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbsws:
      pBSIM4Model->_pbsws = aValue;
      pBSIM4Model->_pbswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbswgs:
      pBSIM4Model->_pbswgs = aValue;
      pBSIM4Model->_pbswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjs:
      pBSIM4Model->_cjs = aValue;
      pBSIM4Model->_cjsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjsws:
      pBSIM4Model->_cjsws = aValue;
      pBSIM4Model->_cjswsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjswgs:
      pBSIM4Model->_cjswgs = aValue;
      pBSIM4Model->_cjswgsGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtid:
      pBSIM4Model->_xtid = aValue;
      pBSIM4Model->_xtidGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__njd:
      pBSIM4Model->_njd = aValue;
      pBSIM4Model->_njdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjd:
      pBSIM4Model->_mjd = aValue;
      pBSIM4Model->_mjdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjswd:
      pBSIM4Model->_mjswd = aValue;
      pBSIM4Model->_mjswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__mjswgd:
      pBSIM4Model->_mjswgd = aValue;
      pBSIM4Model->_mjswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jsd:
      pBSIM4Model->_jsd = aValue;
      pBSIM4Model->_jsdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jswd:
      pBSIM4Model->_jswd = aValue;
      pBSIM4Model->_jswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jswgd:
      pBSIM4Model->_jswgd = aValue;
      pBSIM4Model->_jswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtsd:
      pBSIM4Model->_jtsd = aValue;
      pBSIM4Model->_jtsdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtsswd:
      pBSIM4Model->_jtsswd = aValue;
      pBSIM4Model->_jtsswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__jtsswgd:
      pBSIM4Model->_jtsswgd = aValue;
      pBSIM4Model->_jtsswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjtsd:
      pBSIM4Model->_tnjtsd = aValue;
      pBSIM4Model->_tnjtsdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjtsswd:
      pBSIM4Model->_tnjtsswd = aValue;
      pBSIM4Model->_tnjtsswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__tnjtsswgd:
      pBSIM4Model->_tnjtsswgd = aValue;
      pBSIM4Model->_tnjtsswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtsd:
      pBSIM4Model->_vtsd = aValue;
      pBSIM4Model->_vtsdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtsswd:
      pBSIM4Model->_vtsswd = aValue;
      pBSIM4Model->_vtsswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__vtsswgd:
      pBSIM4Model->_vtsswgd = aValue;
      pBSIM4Model->_vtsswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtsd:
      pBSIM4Model->_xtsd = aValue;
      pBSIM4Model->_xtsdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtsswd:
      pBSIM4Model->_xtsswd = aValue;
      pBSIM4Model->_xtsswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__xtsswgd:
      pBSIM4Model->_xtsswgd = aValue;
      pBSIM4Model->_xtsswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbd:
      pBSIM4Model->_pbd = aValue;
      pBSIM4Model->_pbdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbswd:
      pBSIM4Model->_pbswd = aValue;
      pBSIM4Model->_pbswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__pbswgd:
      pBSIM4Model->_pbswgd = aValue;
      pBSIM4Model->_pbswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjd:
      pBSIM4Model->_cjd = aValue;
      pBSIM4Model->_cjdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjswd:
      pBSIM4Model->_cjswd = aValue;
      pBSIM4Model->_cjswdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__cjswgd:
      pBSIM4Model->_cjswgd = aValue;
      pBSIM4Model->_cjswgdGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__dwj:
      pBSIM4Model->_dwj = aValue;
      pBSIM4Model->_dwjGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__wlc:
      pBSIM4Model->_wlc = aValue;
      pBSIM4Model->_wlcGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__wln:
      pBSIM4Model->_wln = aValue;
      pBSIM4Model->_wlnGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__wwc:
      pBSIM4Model->_wwc = aValue;
      pBSIM4Model->_wwcGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__wwn:
      pBSIM4Model->_wwn = aValue;
      pBSIM4Model->_wwnGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD__wwlc:
      pBSIM4Model->_wwlc = aValue;
      pBSIM4Model->_wwlcGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_omimod:
      pBSIM4Model->omimod = aValue;
      pBSIM4Model->omimodGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_agemod:
      pBSIM4Model->agemod = (int)aValue;
      pBSIM4Model->agemodGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_fvth0_age:
      pBSIM4Model->fvth0_age = aValue;
      pBSIM4Model->fvth0_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_dagetime:
      pBSIM4Model->dagetime = aValue;
      pBSIM4Model->dagetimeGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_n_age:
      pBSIM4Model->n_age = aValue;
      pBSIM4Model->n_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_Hs_age:
      pBSIM4Model->Hs_age = aValue;
      pBSIM4Model->Hs_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_ms_age:
      pBSIM4Model->ms_age = aValue;
      pBSIM4Model->ms_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_Hg_age:
      pBSIM4Model->Hg_age = aValue;
      pBSIM4Model->Hg_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_mg_age:
      pBSIM4Model->mg_age = aValue;
      pBSIM4Model->mg_ageGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;

    case B4_MOD_Vgsdmax:
      pBSIM4Model->Vgsdmax = aValue;
      pBSIM4Model->VgsdmaxGiven = TRUE;
      if(ModNameUpdate==1) aName[0] = '_';
      break;


/***************************/
    case B4_MOD_toxe:
      pBSIM4Model->toxe = aValue;
      pBSIM4Model->toxeGiven = TRUE;
      break;

    case B4_MOD_xl:
      pBSIM4Model->xl = aValue;
      pBSIM4Model->xlGiven = TRUE;
      break;

    case B4_MOD_xw:
      pBSIM4Model->xw = aValue;
      pBSIM4Model->xwGiven = TRUE;
      break;

    case B4_MOD_vth0:
      pBSIM4Model->vth0 = aValue;
      pBSIM4Model->vth0Given = TRUE;
      break;

    case B4_MOD_lvth0:
      pBSIM4Model->lvth0 = aValue;
      pBSIM4Model->lvth0Given = TRUE;
      break;

    case B4_MOD_wvth0:
      pBSIM4Model->wvth0 = aValue;
      pBSIM4Model->wvth0Given = TRUE;
      break;

    case B4_MOD_pvth0:
      pBSIM4Model->pvth0 = aValue;
      pBSIM4Model->pvth0Given = TRUE;
      break;

    case B4_MOD_k2:
      pBSIM4Model->k2 = aValue;
      pBSIM4Model->k2Given = TRUE;
      break;

    case B4_MOD_u0:
      pBSIM4Model->u0 = aValue;
      pBSIM4Model->u0Given = TRUE;
      break;

    case B4_MOD_lu0:
      pBSIM4Model->lu0 = aValue;
      pBSIM4Model->lu0Given = TRUE;
      break;

    case B4_MOD_wu0:
      pBSIM4Model->wu0 = aValue;
      pBSIM4Model->wu0Given = TRUE;
      break;

    case B4_MOD_pu0:
      pBSIM4Model->pu0 = aValue;
      pBSIM4Model->pu0Given = TRUE;
      break;

    case B4_MOD_eta0:
      pBSIM4Model->eta0 = aValue;
      pBSIM4Model->eta0Given = TRUE;
      break;

    case B4_MOD_vsat:
      pBSIM4Model->vsat = aValue;
      pBSIM4Model->vsatGiven = TRUE;
      break;

    case B4_MOD_lvsat:
      pBSIM4Model->lvsat = aValue;
      pBSIM4Model->lvsatGiven = TRUE;
      break;

    case B4_MOD_wvsat:
      pBSIM4Model->wvsat = aValue;
      pBSIM4Model->wvsatGiven = TRUE;
      break;

    case B4_MOD_pvsat:
      pBSIM4Model->pvsat = aValue;
      pBSIM4Model->pvsatGiven = TRUE;
      break;

    case B4_MOD_dmci:
      pBSIM4Model->dmci = aValue;
      pBSIM4Model->dmciGiven = TRUE;
      break;

    case B4_MOD_dmcg:
      pBSIM4Model->dmcg = aValue;
      pBSIM4Model->dmcgGiven = TRUE;
      break;

    case B4_MOD_tnom:
      pBSIM4Model->tnom = aValue;
      pBSIM4Model->tnomGiven = TRUE;
      break;

    default:
      break;
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4SetModelParam.c,v $ */
