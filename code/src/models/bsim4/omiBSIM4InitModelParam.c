/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4InitModelParam.c
 *  Date        : 2010_1123
 *  Description : To initialize model parameters
 */


#include "omiBSIM4Def.h"


int omiBSIM4InitModelParam (omiBSIM4Model *pBSIM4Model)
{
  pBSIM4Model->tox_cGiven=0,   pBSIM4Model->tox_gGiven=0,   pBSIM4Model->tox_maxGiven=0,   pBSIM4Model->tox_minGiven=0;
  pBSIM4Model->dxl_cGiven=0,   pBSIM4Model->dxl_gGiven=0,   pBSIM4Model->dxl_maxGiven=0,   pBSIM4Model->dxl_minGiven=0;
  pBSIM4Model->dxw_cGiven=0,   pBSIM4Model->dxw_gGiven=0,   pBSIM4Model->dxw_maxGiven=0,   pBSIM4Model->dxw_minGiven=0;
  pBSIM4Model->dvth_cGiven=0,   pBSIM4Model->dvth_gGiven=0,   pBSIM4Model->dvth_maxGiven=0,   pBSIM4Model->dvth_minGiven=0;
  pBSIM4Model->dlvth_cGiven=0,   pBSIM4Model->dlvth_gGiven=0,   pBSIM4Model->dlvth_maxGiven=0,   pBSIM4Model->dlvth_minGiven=0;
  pBSIM4Model->dwvth_cGiven=0,   pBSIM4Model->dwvth_gGiven=0,   pBSIM4Model->dwvth_maxGiven=0,   pBSIM4Model->dwvth_minGiven=0;
  pBSIM4Model->dpvth_cGiven=0,   pBSIM4Model->dpvth_gGiven=0,   pBSIM4Model->dpvth_maxGiven=0,   pBSIM4Model->dpvth_minGiven=0;
  pBSIM4Model->du0_cGiven=0,   pBSIM4Model->du0_gGiven=0,   pBSIM4Model->du0_maxGiven=0,   pBSIM4Model->du0_minGiven=0;
  pBSIM4Model->dlu0_cGiven=0,   pBSIM4Model->dlu0_gGiven=0,   pBSIM4Model->dlu0_maxGiven=0,   pBSIM4Model->dlu0_minGiven=0;
  pBSIM4Model->dwu0_cGiven=0,   pBSIM4Model->dwu0_gGiven=0,   pBSIM4Model->dwu0_maxGiven=0,   pBSIM4Model->dwu0_minGiven=0;
  pBSIM4Model->dpu0_cGiven=0,   pBSIM4Model->dpu0_gGiven=0,   pBSIM4Model->dpu0_maxGiven=0,   pBSIM4Model->dpu0_minGiven=0;
  pBSIM4Model->dvsat_cGiven=0,   pBSIM4Model->dvsat_gGiven=0,   pBSIM4Model->dvsat_maxGiven=0,   pBSIM4Model->dvsat_minGiven=0;
  pBSIM4Model->dlvsat_cGiven=0,   pBSIM4Model->dlvsat_gGiven=0,   pBSIM4Model->dlvsat_maxGiven=0,   pBSIM4Model->dlvsat_minGiven=0;
  pBSIM4Model->dwvsat_cGiven=0,   pBSIM4Model->dwvsat_gGiven=0,   pBSIM4Model->dwvsat_maxGiven=0,   pBSIM4Model->dwvsat_minGiven=0;
  pBSIM4Model->dpvsat_cGiven=0,   pBSIM4Model->dpvsat_gGiven=0,   pBSIM4Model->dpvsat_maxGiven=0,   pBSIM4Model->dpvsat_minGiven=0;

  pBSIM4Model->delvtoGiven=0,pBSIM4Model->mulu0Given=0;

  pBSIM4Model->mis_a_1Given=0,pBSIM4Model->mis_a_2Given=0;

  pBSIM4Model->parl1Given=0,pBSIM4Model->parl2Given=0;

  pBSIM4Model->saref0Given=0,pBSIM4Model->sbref0Given=0,pBSIM4Model->wlod0Given=0,pBSIM4Model->ku00Given=0,pBSIM4Model->lku00Given=0;
  pBSIM4Model->wku00Given=0,pBSIM4Model->pku00Given=0,pBSIM4Model->tku00Given=0,pBSIM4Model->llodku00Given=0,pBSIM4Model->wlodku00Given=0;
  pBSIM4Model->kvsat0Given=0,pBSIM4Model->kvth00Given=0,pBSIM4Model->lkvth00Given=0,pBSIM4Model->wkvth00Given=0,pBSIM4Model->pkvth00Given=0;
  pBSIM4Model->llodvth0Given=0,pBSIM4Model->wlodvth0Given=0,pBSIM4Model->stk20Given=0,pBSIM4Model->lodk20Given=0,pBSIM4Model->steta00Given=0;
  pBSIM4Model->lodeta00Given=0;

  pBSIM4Model->rn0xbGiven=0;

  pBSIM4Model->_tcjGiven=0,pBSIM4Model->_tcjswGiven=0,pBSIM4Model->_tcjswgGiven=0,pBSIM4Model->_tpbGiven=0,pBSIM4Model->_tpbswGiven=0;
  pBSIM4Model->_tpbswgGiven=0,pBSIM4Model->_xtisGiven=0,pBSIM4Model->_njsGiven=0,pBSIM4Model->_bvsGiven=0,pBSIM4Model->_mjsGiven=0;
  pBSIM4Model->_mjswsGiven=0,pBSIM4Model->_mjswgsGiven=0,pBSIM4Model->_jssGiven=0,pBSIM4Model->_jswsGiven=0,pBSIM4Model->_jswgsGiven=0;
  pBSIM4Model->_jtssGiven=0,pBSIM4Model->_jtsswsGiven=0,pBSIM4Model->_jtsswgsGiven=0,pBSIM4Model->_njtsGiven=0,pBSIM4Model->_njtsswGiven=0;
  pBSIM4Model->_njtsswgGiven=0,pBSIM4Model->_njtsdxGiven=0,pBSIM4Model->_njtsswdxGiven=0,pBSIM4Model->_njtsswgdxGiven=0,pBSIM4Model->_tnjtsGiven=0;
  pBSIM4Model->_tnjtsswGiven=0,pBSIM4Model->_tnjtsswgGiven=0,pBSIM4Model->_vtssGiven=0,pBSIM4Model->_vtsswsGiven=0,pBSIM4Model->_vtsswgsGiven=0;
  pBSIM4Model->_xtssGiven=0,pBSIM4Model->_xtsswsGiven=0,pBSIM4Model->_xtsswgsGiven=0,pBSIM4Model->_pbsGiven=0,pBSIM4Model->_pbswsGiven=0;
  pBSIM4Model->_pbswgsGiven=0,pBSIM4Model->_cjsGiven=0,pBSIM4Model->_cjswsGiven=0,pBSIM4Model->_cjswgsGiven=0,pBSIM4Model->_xtidGiven=0;
  pBSIM4Model->_njdGiven=0,pBSIM4Model->_mjdGiven=0,pBSIM4Model->_mjswdGiven=0,pBSIM4Model->_mjswgdGiven=0,pBSIM4Model->_jsdGiven=0;
  pBSIM4Model->_jswdGiven=0,pBSIM4Model->_jswgdGiven=0,pBSIM4Model->_jtsdGiven=0,pBSIM4Model->_jtsswdGiven=0,pBSIM4Model->_jtsswgdGiven=0;
  pBSIM4Model->_tnjtsdGiven=0,pBSIM4Model->_tnjtsswdGiven=0,pBSIM4Model->_tnjtsswgdGiven=0,pBSIM4Model->_vtsdGiven=0,pBSIM4Model->_vtsswdGiven=0;
  pBSIM4Model->_vtsswgdGiven=0,pBSIM4Model->_xtsdGiven=0,pBSIM4Model->_xtsswdGiven=0,pBSIM4Model->_xtsswgdGiven=0,pBSIM4Model->_pbdGiven=0;
  pBSIM4Model->_pbswdGiven=0,pBSIM4Model->_pbswgdGiven=0,pBSIM4Model->_cjdGiven=0,pBSIM4Model->_cjswdGiven=0,pBSIM4Model->_cjswgdGiven=0;
  pBSIM4Model->_dwjGiven=0,pBSIM4Model->_wlcGiven=0,pBSIM4Model->_wlnGiven=0,pBSIM4Model->_wwcGiven=0,pBSIM4Model->_wwnGiven=0;
  pBSIM4Model->_wwlcGiven=0;

  pBSIM4Model->omimodGiven=0;

  pBSIM4Model->agemodGiven=0,pBSIM4Model->fvth0_ageGiven=0,pBSIM4Model->dagetimeGiven=0,pBSIM4Model->n_ageGiven=0,pBSIM4Model->Hs_ageGiven=0;
  pBSIM4Model->ms_ageGiven=0,pBSIM4Model->Hg_ageGiven=0,pBSIM4Model->mg_ageGiven=0;

  /* BSIM4 model parameters */
  pBSIM4Model->toxeGiven=0;
  pBSIM4Model->xlGiven=0;
  pBSIM4Model->xwGiven=0;
  pBSIM4Model->vth0Given=0;
  pBSIM4Model->lvth0Given=0;
  pBSIM4Model->wvth0Given=0;
  pBSIM4Model->pvth0Given=0;
  pBSIM4Model->k2Given=0;
  pBSIM4Model->eta0Given=0;
  pBSIM4Model->u0Given=0;
  pBSIM4Model->lu0Given=0;
  pBSIM4Model->wu0Given=0;
  pBSIM4Model->pu0Given=0;
  pBSIM4Model->vsatGiven=0;
  pBSIM4Model->lvsatGiven=0;
  pBSIM4Model->wvsatGiven=0;
  pBSIM4Model->pvsatGiven=0;
  pBSIM4Model->dmciGiven=0;
  pBSIM4Model->dmcgGiven=0;
  pBSIM4Model->tnomGiven=0;

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4InitModelParam.c,v $ */
