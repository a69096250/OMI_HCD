/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Set.c
 *  Date        : 2010_1123
 *  Description : To set default values
 */


#include <math.h>
#include "omiBSIM4Def.h"


int omiBSIM4SetModelParamDefault (omiBSIM4Model *pBSIM4Model)
{
  if (!pBSIM4Model->toxeGiven)
    pBSIM4Model->toxe = 3.0e-9;
  if (!pBSIM4Model->xlGiven)
    pBSIM4Model->xl = 0.0;
  if (!pBSIM4Model->xwGiven)
    pBSIM4Model->xw = 0.0;
  if (!pBSIM4Model->vth0Given)
  {
    if(pBSIM4Model->modelType == NMOS) pBSIM4Model->vth0 = 0.7;
    else pBSIM4Model->vth0 = -0.7;
  }
  if (!pBSIM4Model->lvth0Given)
    pBSIM4Model->lvth0 = 0.0;
  if (!pBSIM4Model->wvth0Given)
    pBSIM4Model->wvth0 = 0.0;
  if (!pBSIM4Model->pvth0Given)
    pBSIM4Model->pvth0 = 0.0;
  if (!pBSIM4Model->k2Given)
    pBSIM4Model->k2 = 0.0;
  if (!pBSIM4Model->u0Given)
  {
    if(pBSIM4Model->modelType == NMOS) pBSIM4Model->u0 = 0.067;
    else pBSIM4Model->u0 = 0.025;
  }
  if (!pBSIM4Model->lu0Given)
    pBSIM4Model->lu0 = 0.0;
  if (!pBSIM4Model->wu0Given)
    pBSIM4Model->wu0 = 0.0;
  if (!pBSIM4Model->pu0Given)
    pBSIM4Model->pu0 = 0.0;
  if (!pBSIM4Model->eta0Given)
    pBSIM4Model->eta0 = 0.08;
  if (!pBSIM4Model->vsatGiven)
    pBSIM4Model->vsat = 8.0e4;
  if (!pBSIM4Model->lvsatGiven)
    pBSIM4Model->lvsat = 0.0;
  if (!pBSIM4Model->wvsatGiven)
    pBSIM4Model->wvsat = 0.0;
  if (!pBSIM4Model->pvsatGiven)
    pBSIM4Model->pvsat = 0.0;
  if (!pBSIM4Model->dmciGiven)
    pBSIM4Model->dmci = 0.0;
  if (!pBSIM4Model->dmcgGiven)
    pBSIM4Model->dmcg = 0.0;
  if (!pBSIM4Model->tnomGiven)
    pBSIM4Model->tnom = 27.0;

/***************************/
  if (!pBSIM4Model->tox_cGiven)
    pBSIM4Model->tox_c = pBSIM4Model->toxe;
  if (!pBSIM4Model->tox_gGiven)
    pBSIM4Model->tox_g = 0.0;
  if (!pBSIM4Model->tox_maxGiven)
    pBSIM4Model->tox_max = -1e99;
  if (!pBSIM4Model->tox_minGiven)
    pBSIM4Model->tox_min = 1e99;
  if (!pBSIM4Model->dxl_cGiven)
    pBSIM4Model->dxl_c = 0.0;
  if (!pBSIM4Model->dxl_gGiven)
    pBSIM4Model->dxl_g = 0.0;
  if (!pBSIM4Model->dxl_maxGiven)
    pBSIM4Model->dxl_max = -1e99;
  if (!pBSIM4Model->dxl_minGiven)
    pBSIM4Model->dxl_min = 1e99;
  if (!pBSIM4Model->dxw_cGiven)
    pBSIM4Model->dxw_c = 0.0;
  if (!pBSIM4Model->dxw_gGiven)
    pBSIM4Model->dxw_g = 0.0;
  if (!pBSIM4Model->dxw_maxGiven)
    pBSIM4Model->dxw_max = -1e99;
  if (!pBSIM4Model->dxw_minGiven)
    pBSIM4Model->dxw_min = 1e99;
  if (!pBSIM4Model->dvth_cGiven)
    pBSIM4Model->dvth_c = 0.0;
  if (!pBSIM4Model->dvth_gGiven)
    pBSIM4Model->dvth_g = 0.0;
  if (!pBSIM4Model->dvth_maxGiven)
    pBSIM4Model->dvth_max = -1e99;
  if (!pBSIM4Model->dvth_minGiven)
    pBSIM4Model->dvth_min = 1e99;
  if (!pBSIM4Model->dlvth_cGiven)
    pBSIM4Model->dlvth_c = 0.0;
  if (!pBSIM4Model->dlvth_gGiven)
    pBSIM4Model->dlvth_g = 0.0;
  if (!pBSIM4Model->dlvth_maxGiven)
    pBSIM4Model->dlvth_max = -1e99;
  if (!pBSIM4Model->dlvth_minGiven)
    pBSIM4Model->dlvth_min = 1e99;
  if (!pBSIM4Model->dwvth_cGiven)
    pBSIM4Model->dwvth_c = 0.0;
  if (!pBSIM4Model->dwvth_gGiven)
    pBSIM4Model->dwvth_g = 0.0;
  if (!pBSIM4Model->dwvth_maxGiven)
    pBSIM4Model->dwvth_max = -1e99;
  if (!pBSIM4Model->dwvth_minGiven)
    pBSIM4Model->dwvth_min = 1e99;
  if (!pBSIM4Model->dpvth_cGiven)
    pBSIM4Model->dpvth_c = 0.0;
  if (!pBSIM4Model->dpvth_gGiven)
    pBSIM4Model->dpvth_g = 0.0;
  if (!pBSIM4Model->dpvth_maxGiven)
    pBSIM4Model->dpvth_max = -1e99;
  if (!pBSIM4Model->dpvth_minGiven)
    pBSIM4Model->dpvth_min = 1e99;
  if (!pBSIM4Model->du0_cGiven)
    pBSIM4Model->du0_c = 0.0;
  if (!pBSIM4Model->du0_gGiven)
    pBSIM4Model->du0_g = 0.0;
  if (!pBSIM4Model->du0_maxGiven)
    pBSIM4Model->du0_max = -1e99;
  if (!pBSIM4Model->du0_minGiven)
    pBSIM4Model->du0_min = 1e99;
  if (!pBSIM4Model->dlu0_cGiven)
    pBSIM4Model->dlu0_c = 0.0;
  if (!pBSIM4Model->dlu0_gGiven)
    pBSIM4Model->dlu0_g = 0.0;
  if (!pBSIM4Model->dlu0_maxGiven)
    pBSIM4Model->dlu0_max = -1e99;
  if (!pBSIM4Model->dlu0_minGiven)
    pBSIM4Model->dlu0_min = 1e99;
  if (!pBSIM4Model->dwu0_cGiven)
    pBSIM4Model->dwu0_c = 0.0;
  if (!pBSIM4Model->dwu0_gGiven)
    pBSIM4Model->dwu0_g = 0.0;
  if (!pBSIM4Model->dwu0_maxGiven)
    pBSIM4Model->dwu0_max = -1e99;
  if (!pBSIM4Model->dwu0_minGiven)
    pBSIM4Model->dwu0_min = 1e99;
  if (!pBSIM4Model->dpu0_cGiven)
    pBSIM4Model->dpu0_c = 0.0;
  if (!pBSIM4Model->dpu0_gGiven)
    pBSIM4Model->dpu0_g = 0.0;
  if (!pBSIM4Model->dpu0_maxGiven)
    pBSIM4Model->dpu0_max = -1e99;
  if (!pBSIM4Model->dpu0_minGiven)
    pBSIM4Model->dpu0_min = 1e99;
  if (!pBSIM4Model->dvsat_cGiven)
    pBSIM4Model->dvsat_c = 0.0;
  if (!pBSIM4Model->dvsat_gGiven)
    pBSIM4Model->dvsat_g = 0.0;
  if (!pBSIM4Model->dvsat_maxGiven)
    pBSIM4Model->dvsat_max = -1e99;
  if (!pBSIM4Model->dvsat_minGiven)
    pBSIM4Model->dvsat_min = 1e99;
  if (!pBSIM4Model->dlvsat_cGiven)
    pBSIM4Model->dlvsat_c = 0.0;
  if (!pBSIM4Model->dlvsat_gGiven)
    pBSIM4Model->dlvsat_g = 0.0;
  if (!pBSIM4Model->dlvsat_maxGiven)
    pBSIM4Model->dlvsat_max = -1e99;
  if (!pBSIM4Model->dlvsat_minGiven)
    pBSIM4Model->dlvsat_min = 1e99;
  if (!pBSIM4Model->dwvsat_cGiven)
    pBSIM4Model->dwvsat_c = 0.0;
  if (!pBSIM4Model->dwvsat_gGiven)
    pBSIM4Model->dwvsat_g = 0.0;
  if (!pBSIM4Model->dwvsat_maxGiven)
    pBSIM4Model->dwvsat_max = -1e99;
  if (!pBSIM4Model->dwvsat_minGiven)
    pBSIM4Model->dwvsat_min = 1e99;
  if (!pBSIM4Model->dpvsat_cGiven)
    pBSIM4Model->dpvsat_c = 0.0;
  if (!pBSIM4Model->dpvsat_gGiven)
    pBSIM4Model->dpvsat_g = 0.0;
  if (!pBSIM4Model->dpvsat_maxGiven)
    pBSIM4Model->dpvsat_max = -1e99;
  if (!pBSIM4Model->dpvsat_minGiven)
    pBSIM4Model->dpvsat_min = 1e99;

/***************************/
  if (!pBSIM4Model->delvtoGiven)
    pBSIM4Model->delvto = 0.0;
  if (!pBSIM4Model->mulu0Given)
    pBSIM4Model->mulu0 = 1.0;
  if (!pBSIM4Model->mis_a_1Given)
    pBSIM4Model->mis_a_1 = 1;
  if (!pBSIM4Model->mis_a_2Given)
    pBSIM4Model->mis_a_2 = 1;
  if (!pBSIM4Model->parl1Given)
    pBSIM4Model->parl1 = 0;
  if (!pBSIM4Model->parl2Given)
    pBSIM4Model->parl2 = 0;
  if (!pBSIM4Model->saref0Given)
    pBSIM4Model->saref0 = 1e-6;
  if (!pBSIM4Model->sbref0Given)
    pBSIM4Model->sbref0 = 1e-6;
  if (!pBSIM4Model->wlod0Given)
    pBSIM4Model->wlod0 = 0;
  if (!pBSIM4Model->ku00Given)
    pBSIM4Model->ku00 = 0;
  if (!pBSIM4Model->lku00Given)
    pBSIM4Model->lku00 = 0;
  if (!pBSIM4Model->wku00Given)
    pBSIM4Model->wku00 = 0;
  if (!pBSIM4Model->pku00Given)
    pBSIM4Model->pku00 = 0;
  if (!pBSIM4Model->tku00Given)
    pBSIM4Model->tku00 = 0;
  if (!pBSIM4Model->llodku00Given)
    pBSIM4Model->llodku00 = 1;
  if (!pBSIM4Model->wlodku00Given)
    pBSIM4Model->wlodku00 = 1;
  if (!pBSIM4Model->kvsat0Given)
    pBSIM4Model->kvsat0 = 0;
  if (!pBSIM4Model->kvth00Given)
    pBSIM4Model->kvth00 = 0;
  if (!pBSIM4Model->lkvth00Given)
    pBSIM4Model->lkvth00 = 0;
  if (!pBSIM4Model->wkvth00Given)
    pBSIM4Model->wkvth00 = 0;
  if (!pBSIM4Model->pkvth00Given)
    pBSIM4Model->pkvth00 = 0;
  if (!pBSIM4Model->llodvth0Given)
    pBSIM4Model->llodvth0 = 1;
  if (!pBSIM4Model->wlodvth0Given)
    pBSIM4Model->wlodvth0 = 1;
  if (!pBSIM4Model->stk20Given)
    pBSIM4Model->stk20 = 0;
  if (!pBSIM4Model->lodk20Given)
    pBSIM4Model->lodk20 = 1;
  if (!pBSIM4Model->steta00Given)
    pBSIM4Model->steta00 = 0;
  if (!pBSIM4Model->lodeta00Given)
    pBSIM4Model->lodeta00 = 1;
  if (!pBSIM4Model->rn0xbGiven)
    pBSIM4Model->rn0xb = 0;
  if (!pBSIM4Model->_tcjGiven)
    pBSIM4Model->_tcj = 0;
  if (!pBSIM4Model->_tcjswGiven)
    pBSIM4Model->_tcjsw = 0;
  if (!pBSIM4Model->_tcjswgGiven)
    pBSIM4Model->_tcjswg = 0;
  if (!pBSIM4Model->_tpbGiven)
    pBSIM4Model->_tpb = 0;
  if (!pBSIM4Model->_tpbswGiven)
    pBSIM4Model->_tpbsw = 0;
  if (!pBSIM4Model->_tpbswgGiven)
    pBSIM4Model->_tpbswg = 0;
  if (!pBSIM4Model->_xtisGiven)
    pBSIM4Model->_xtis = 0;
  if (!pBSIM4Model->_njsGiven)
    pBSIM4Model->_njs = 1;
  if (!pBSIM4Model->_bvsGiven)
    pBSIM4Model->_bvs = 0;
  if (!pBSIM4Model->_mjsGiven)
    pBSIM4Model->_mjs = 0;
  if (!pBSIM4Model->_mjswsGiven)
    pBSIM4Model->_mjsws = 0;
  if (!pBSIM4Model->_mjswgsGiven)
    pBSIM4Model->_mjswgs = 0;
  if (!pBSIM4Model->_jssGiven)
    pBSIM4Model->_jss = 0;
  if (!pBSIM4Model->_jswsGiven)
    pBSIM4Model->_jsws = 0;
  if (!pBSIM4Model->_jswgsGiven)
    pBSIM4Model->_jswgs = 0;
  if (!pBSIM4Model->_jtssGiven)
    pBSIM4Model->_jtss = 0;
  if (!pBSIM4Model->_jtsswsGiven)
    pBSIM4Model->_jtssws = 0;
  if (!pBSIM4Model->_jtsswgsGiven)
    pBSIM4Model->_jtsswgs = 0;
  if (!pBSIM4Model->_njtsGiven)
    pBSIM4Model->_njts = 0;
  if (!pBSIM4Model->_njtsswGiven)
    pBSIM4Model->_njtssw = 0;
  if (!pBSIM4Model->_njtsswgGiven)
    pBSIM4Model->_njtsswg = 0;
  if (!pBSIM4Model->_njtsdxGiven)
    pBSIM4Model->_njtsdx = 0;
  if (!pBSIM4Model->_njtsswdxGiven)
    pBSIM4Model->_njtsswdx = 0;
  if (!pBSIM4Model->_njtsswgdxGiven)
    pBSIM4Model->_njtsswgdx = 0;
  if (!pBSIM4Model->_tnjtsGiven)
    pBSIM4Model->_tnjts = 0;
  if (!pBSIM4Model->_tnjtsswGiven)
    pBSIM4Model->_tnjtssw = 0;
  if (!pBSIM4Model->_tnjtsswgGiven)
    pBSIM4Model->_tnjtsswg = 0;
  if (!pBSIM4Model->_vtssGiven)
    pBSIM4Model->_vtss = 0;
  if (!pBSIM4Model->_vtsswsGiven)
    pBSIM4Model->_vtssws = 0;
  if (!pBSIM4Model->_vtsswgsGiven)
    pBSIM4Model->_vtsswgs = 0;
  if (!pBSIM4Model->_xtssGiven)
    pBSIM4Model->_xtss = 0;
  if (!pBSIM4Model->_xtsswsGiven)
    pBSIM4Model->_xtssws = 0;
  if (!pBSIM4Model->_xtsswgsGiven)
    pBSIM4Model->_xtsswgs = 0;
  if (!pBSIM4Model->_pbsGiven)
    pBSIM4Model->_pbs = 0;
  if (!pBSIM4Model->_pbswsGiven)
    pBSIM4Model->_pbsws = 0;
  if (!pBSIM4Model->_pbswgsGiven)
    pBSIM4Model->_pbswgs = 0;
  if (!pBSIM4Model->_cjsGiven)
    pBSIM4Model->_cjs = 0;
  if (!pBSIM4Model->_cjswsGiven)
    pBSIM4Model->_cjsws = 0;
  if (!pBSIM4Model->_cjswgsGiven)
    pBSIM4Model->_cjswgs = 0;
  if (!pBSIM4Model->_xtidGiven)
    pBSIM4Model->_xtid = 0;
  if (!pBSIM4Model->_njdGiven)
    pBSIM4Model->_njd = 1;
  if (!pBSIM4Model->_mjdGiven)
    pBSIM4Model->_mjd = 0;
  if (!pBSIM4Model->_mjswdGiven)
    pBSIM4Model->_mjswd = 0;
  if (!pBSIM4Model->_mjswgdGiven)
    pBSIM4Model->_mjswgd = 0;
  if (!pBSIM4Model->_jsdGiven)
    pBSIM4Model->_jsd = 0;
  if (!pBSIM4Model->_jswdGiven)
    pBSIM4Model->_jswd = 0;
  if (!pBSIM4Model->_jswgdGiven)
    pBSIM4Model->_jswgd = 0;
  if (!pBSIM4Model->_jtsdGiven)
    pBSIM4Model->_jtsd = 0;
  if (!pBSIM4Model->_jtsswdGiven)
    pBSIM4Model->_jtsswd = 0;
  if (!pBSIM4Model->_jtsswgdGiven)
    pBSIM4Model->_jtsswgd = 0;
  if (!pBSIM4Model->_tnjtsdGiven)
    pBSIM4Model->_tnjtsd = 0;
  if (!pBSIM4Model->_tnjtsswdGiven)
    pBSIM4Model->_tnjtsswd = 0;
  if (!pBSIM4Model->_tnjtsswgdGiven)
    pBSIM4Model->_tnjtsswgd = 0;
  if (!pBSIM4Model->_vtsdGiven)
    pBSIM4Model->_vtsd = 0;
  if (!pBSIM4Model->_vtsswdGiven)
    pBSIM4Model->_vtsswd = 0;
  if (!pBSIM4Model->_vtsswgdGiven)
    pBSIM4Model->_vtsswgd = 0;
  if (!pBSIM4Model->_xtsdGiven)
    pBSIM4Model->_xtsd = 0;
  if (!pBSIM4Model->_xtsswdGiven)
    pBSIM4Model->_xtsswd = 0;
  if (!pBSIM4Model->_xtsswgdGiven)
    pBSIM4Model->_xtsswgd = 0;
  if (!pBSIM4Model->_pbdGiven)
    pBSIM4Model->_pbd = 0;
  if (!pBSIM4Model->_pbswdGiven)
    pBSIM4Model->_pbswd = 0;
  if (!pBSIM4Model->_pbswgdGiven)
    pBSIM4Model->_pbswgd = 0;
  if (!pBSIM4Model->_cjdGiven)
    pBSIM4Model->_cjd = 0;
  if (!pBSIM4Model->_cjswdGiven)
    pBSIM4Model->_cjswd = 0;
  if (!pBSIM4Model->_cjswgdGiven)
    pBSIM4Model->_cjswgd = 0;
  if (!pBSIM4Model->_dwjGiven)
    pBSIM4Model->_dwj = 0;
  if (!pBSIM4Model->_wlcGiven)
    pBSIM4Model->_wlc = 0;
  if (!pBSIM4Model->_wlnGiven)
    pBSIM4Model->_wln = 0;
  if (!pBSIM4Model->_wwcGiven)
    pBSIM4Model->_wwc = 0;
  if (!pBSIM4Model->_wwnGiven)
    pBSIM4Model->_wwn = 0;
  if (!pBSIM4Model->_wwlcGiven)
    pBSIM4Model->_wwlc = 0;
  if (!pBSIM4Model->omimodGiven)
    pBSIM4Model->omimod = 0;
  if (!pBSIM4Model->agemodGiven)
    pBSIM4Model->agemod = 0;
  if (!pBSIM4Model->fvth0_ageGiven)
    pBSIM4Model->fvth0_age = 1;
  if (!pBSIM4Model->dagetimeGiven)
    pBSIM4Model->dagetime = 0;
  if (!pBSIM4Model->n_ageGiven)
    pBSIM4Model->n_age = 0.3;
  if (!pBSIM4Model->Hs_ageGiven)
    pBSIM4Model->Hs_age = 1;
  if (!pBSIM4Model->ms_ageGiven)
    pBSIM4Model->ms_age = 3;
  if (!pBSIM4Model->Hg_ageGiven)
    pBSIM4Model->Hg_age = 1;
  if (!pBSIM4Model->mg_ageGiven)
    pBSIM4Model->mg_age = 3;
  if (!pBSIM4Model->VgsdmaxGiven)
    pBSIM4Model->Vgsdmax = 1000;

  return OMI_OK;
}


int omiBSIM4SetInstParamDefault (omiCKT *pCKT, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst)
{
  double wef,lef;
   
  if (!pBSIM4Inst->lGiven)
    pBSIM4Inst->l = 10e-6;
  if (!pBSIM4Inst->wGiven)
    pBSIM4Inst->w = 10e-6;
  if (!pBSIM4Inst->mGiven)
    pBSIM4Inst->m = 1;
  if (!pBSIM4Inst->multiGiven)
    pBSIM4Inst->multi = 1;
  if (!pBSIM4Inst->nfGiven)
    pBSIM4Inst->nf = 1.0;
  if (!pBSIM4Inst->scaleGiven)
    pBSIM4Inst->scale = pCKT->scale;
   
  lef=(pBSIM4Inst->l)*pBSIM4Inst->scale;
  wef=(pBSIM4Inst->w/pBSIM4Inst->nf)*pBSIM4Inst->scale;

   
  if (!pBSIM4Inst->_dmcgGiven)
    pBSIM4Inst->_dmcg = pBSIM4Model->dmcg;
  if (!pBSIM4Inst->_dmciGiven)
    pBSIM4Inst->_dmci = pBSIM4Model->dmci;
  
  if ((!pBSIM4Inst->saGiven)||(pBSIM4Inst->sa<1e-10))
    pBSIM4Inst->sa = pBSIM4Model->saref0/pBSIM4Inst->scale;
  if ((!pBSIM4Inst->sbGiven)||(pBSIM4Inst->sb<1e-10))
    pBSIM4Inst->sb = pBSIM4Model->sbref0/pBSIM4Inst->scale;
  if (!pBSIM4Inst->sdGiven)
    pBSIM4Inst->sd = 2*pBSIM4Inst->_dmcg/pBSIM4Inst->scale;
  if (!pBSIM4Inst->scaGiven)
    pBSIM4Inst->sca = 0;
  if (!pBSIM4Inst->scbGiven)
    pBSIM4Inst->scb = 0;
  if (!pBSIM4Inst->sccGiven)
    pBSIM4Inst->scc = 0;

  if (!pBSIM4Inst->_delvtoGiven)
    pBSIM4Inst->_delvto = pBSIM4Model->delvto;
  if (!pBSIM4Inst->_mulu0Given)
    pBSIM4Inst->_mulu0 = pBSIM4Model->mulu0;
  if (!pBSIM4Inst->prnflagGiven)
    pBSIM4Inst->prnflag = 0.0;

  return OMI_OK;
}


int omiBSIM4PrintModel (omiModel *pModel, omiBSIM4Model *pBSIM4Model)
{
  if (!pBSIM4Model->printModel)
    return OMI_OK;


  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4Set.c,v $ */
