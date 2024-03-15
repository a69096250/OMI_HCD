/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Temp.c
 *  Date        : 2010_1123
 *  Description : To evaluate LOD/Mismatch equations,
 *                to update model parameters,
 *                to check illegal value
 */


#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omiBSIM4Def.h"


static int omiBSIM4ExtraploateAge (omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst);
static int omiBSIM4DegradeAge (omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst);
extern void omiFreeElem (char *key, void *data);


int omiBSIM4Temp (omiCKT *pCKT, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst)
{
  int i = 0;

  /* model type 
  int modelType = pBSIM4Model->modelType;*/

  /* simulation temperautre */
  double temper = pCKT->CKTtemp;

  /* instance parameters */
  double l = pBSIM4Inst->l;
  double w = pBSIM4Inst->w;
  double nf = pBSIM4Inst->nf;
  double ad = pBSIM4Inst->ad;
  double as = pBSIM4Inst->as;
  double pd = pBSIM4Inst->pd;
  double ps = pBSIM4Inst->ps;
  double nrd = pBSIM4Inst->nrd;
  double nrs = pBSIM4Inst->nrs;
  double sa = pBSIM4Inst->sa;
  double sb = pBSIM4Inst->sb;
  double sd = pBSIM4Inst->sd;
  double sca = pBSIM4Inst->sca;
  double scb = pBSIM4Inst->scb;
  double scc = pBSIM4Inst->scc;

  double scale=pBSIM4Inst->scale;
  double _dmcg=pBSIM4Inst->_dmcg;
  double _dmci=pBSIM4Inst->_dmci;
  double _xw=pBSIM4Inst->_xw;
  double _xl=pBSIM4Inst->_xl;
  int    prnflag=(int)pBSIM4Inst->prnflag;


  double mis_a_1=pBSIM4Model->mis_a_1;
  double mis_a_2=pBSIM4Model->mis_a_2;

  double parl1=pBSIM4Model->parl1;
  double parl2=pBSIM4Model->parl2;

  double saref0=pBSIM4Model->saref0;
  double sbref0=pBSIM4Model->sbref0;
  double wlod0=pBSIM4Model->wlod0;
  double ku00=pBSIM4Model->ku00;
  double lku00=pBSIM4Model->lku00;
  double wku00=pBSIM4Model->wku00;
  double pku00=pBSIM4Model->pku00;
  double tku00=pBSIM4Model->tku00;
  double llodku00=pBSIM4Model->llodku00;
  double wlodku00=pBSIM4Model->wlodku00;
  double kvsat0=pBSIM4Model->kvsat0;
  double kvth00=pBSIM4Model->kvth00;
  double lkvth00=pBSIM4Model->lkvth00;
  double wkvth00=pBSIM4Model->wkvth00;
  double pkvth00=pBSIM4Model->pkvth00;
  double llodvth0=pBSIM4Model->llodvth0;
  double wlodvth0=pBSIM4Model->wlodvth0;
  double stk20=pBSIM4Model->stk20;
  double lodk20=pBSIM4Model->lodk20;
  double steta00=pBSIM4Model->steta00;
  double lodeta00=pBSIM4Model->lodeta00;

  /* temporary BSIM4 model parameters */
  double toxe_t=0,xl_t=0,xw_t=0,vth0_t=0,lvth0_t=0;
  double wvth0_t=0,pvth0_t=0,k2_t=0,eta0_t=0,u0_t=0;
  double lu0_t=0,wu0_t=0,pu0_t=0,vsat_t=0,lvsat_t=0;
  double wvsat_t=0,pvsat_t=0;

  /* global & local skew parameter */
  double tox_all=0;
  double dxl_global=0,dxl_local=0, dxl_all=0;
  double dxw_global=0,dxw_local=0, dxw_all=0;
  double dvth_all=0;
  double dlvth_all=0;
  double dwvth_all=0;
  double dpvth_all=0;
  double du0_all=0;
  double dlu0_all=0;
  double dwu0_all=0;
  double dpu0_all=0;
  double dvsat_all=0;
  double dlvsat_all=0;
  double dwvsat_all=0;
  double dpvsat_all=0;

  /* Ratio parameters */
  double lef=0;
  double wef=0;


  /* LOD model parameters */
  double inv_sa=0.0;
  double inv_sb=0.0;
  double inv_saref=0.0;
  double inv_sbref=0.0;
  double kstress_u0=0.0;
  double kstress_vth0=0.0;
  double rho_ueff=0.0;
  double rho_ueffref=0.0;

  double dvths_lod=0.0;
  double fu0_lod=0.0;
  double fvsat_lod=0.0;
  double deta0_lod=0.0;
  double dk2_lod=0.0;
  
  int iret=0;
  
  /* External junction diode param */
  double _tcj=pBSIM4Model->_tcj;
  double _tcjsw=pBSIM4Model->_tcjsw;
  double _tcjswg=pBSIM4Model->_tcjswg;
  double _tpb=pBSIM4Model->_tpb;
  double _tpbsw=pBSIM4Model->_tpbsw;
  double _tpbswg=pBSIM4Model->_tpbswg;
  double _xtis=pBSIM4Model->_xtis;
  double _njs=pBSIM4Model->_njs;
  double _mjs=pBSIM4Model->_mjs;
  double _mjsws=pBSIM4Model->_mjsws;
  double _mjswgs=pBSIM4Model->_mjswgs;
  double _jss=pBSIM4Model->_jss;
  double _jsws=pBSIM4Model->_jsws;
  double _jswgs=pBSIM4Model->_jswgs;
  double _jtss=pBSIM4Model->_jtss;
  double _jtssws=pBSIM4Model->_jtssws;
  double _jtsswgs=pBSIM4Model->_jtsswgs;
  double _njts=pBSIM4Model->_njts;
  double _njtssw=pBSIM4Model->_njtssw;
  double _njtsswg=pBSIM4Model->_njtsswg;
  double _njtsdx=pBSIM4Model->_njtsdx;
  double _njtsswdx=pBSIM4Model->_njtsswdx;
  double _njtsswgdx=pBSIM4Model->_njtsswgdx;
  double _tnjts=pBSIM4Model->_tnjts;
  double _tnjtssw=pBSIM4Model->_tnjtssw;
  double _tnjtsswg=pBSIM4Model->_tnjtsswg;
  double _vtss=pBSIM4Model->_vtss;
  double _vtssws=pBSIM4Model->_vtssws;
  double _vtsswgs=pBSIM4Model->_vtsswgs;
  double _xtss=pBSIM4Model->_xtss;
  double _xtssws=pBSIM4Model->_xtssws;
  double _xtsswgs=pBSIM4Model->_xtsswgs;
  double _pbs=pBSIM4Model->_pbs;
  double _pbsws=pBSIM4Model->_pbsws;
  double _pbswgs=pBSIM4Model->_pbswgs;
  double _cjs=pBSIM4Model->_cjs;
  double _cjsws=pBSIM4Model->_cjsws;
  double _cjswgs=pBSIM4Model->_cjswgs;
  double _xtid=pBSIM4Model->_xtid;
  double _njd=pBSIM4Model->_njd;
  double _mjd=pBSIM4Model->_mjd;
  double _mjswd=pBSIM4Model->_mjswd;
  double _mjswgd=pBSIM4Model->_mjswgd;
  double _jsd=pBSIM4Model->_jsd;
  double _jswd=pBSIM4Model->_jswd;
  double _jswgd=pBSIM4Model->_jswgd;
  double _jtsd=pBSIM4Model->_jtsd;
  double _jtsswd=pBSIM4Model->_jtsswd;
  double _jtsswgd=pBSIM4Model->_jtsswgd;
  double _tnjtsd=pBSIM4Model->_tnjtsd;
  double _tnjtsswd=pBSIM4Model->_tnjtsswd;
  double _tnjtsswgd=pBSIM4Model->_tnjtsswgd;
  double _vtsd=pBSIM4Model->_vtsd;
  double _vtsswd=pBSIM4Model->_vtsswd;
  double _vtsswgd=pBSIM4Model->_vtsswgd;
  double _xtsd=pBSIM4Model->_xtsd;
  double _xtsswd=pBSIM4Model->_xtsswd;
  double _xtsswgd=pBSIM4Model->_xtsswgd;
  double _pbd=pBSIM4Model->_pbd;
  double _pbswd=pBSIM4Model->_pbswd;
  double _pbswgd=pBSIM4Model->_pbswgd;
  double _cjd=pBSIM4Model->_cjd;
  double _cjswd=pBSIM4Model->_cjswd;
  double _cjswgd=pBSIM4Model->_cjswgd;
  double _dwj=pBSIM4Model->_dwj;
  double _wlc=pBSIM4Model->_wlc;
  double _wln=pBSIM4Model->_wln;
  double _wwc=pBSIM4Model->_wwc;
  double _wwn=pBSIM4Model->_wwn;
  double _wwlc=pBSIM4Model->_wwlc;

  double  _q=1.609e-19;
  double _kb=1.3806226e-23;
  double _tnom=pBSIM4Model->tnom;
  double _nf=pBSIM4Inst->nf;

  double _vt =0, _vt_tnom =0, _eg_tnom =0, _eg =0, common0 =0, common1 =0, common2 =0;      
  double weffcj =0, _adeff =0, _aseff =0, _pdeff =0, _pseff =0;  
  double jtsswgs =0, jtssws =0, jtss =0, njtsswg =0, njtssw =0, njts =0, Isbs =0;      
  double pbs =0, pbsws =0, pbswgs =0, cjs =0, cjsws =0, cjswgs =0;        
  double jtsswgd =0, jtsswd =0, jtsd =0, njtsswgd =0, njtsswd =0, njtsd =0, Isbd =0;      
  double pbd =0, pbswd =0, pbswgd =0, cjd =0, cjswd =0, cjswgd =0;
  double xtis=0,xtid=0;

  /* evaluate ratio */
  lef=(l)*scale;
  wef=(w/nf)*scale;

  /* evaluate W & L equations */
  if (pCKT->evalType == evalTypeWL)
  {
    if(prnflag==1) omiPrint(" evaltype=%d",pCKT->evalType);
    dxl_global =pBSIM4Model->dxl_g;
    dxw_global =pBSIM4Model->dxw_g;
    dxl_local =parl1*mis_a_1;
    dxw_local =parl2*mis_a_2;

    /*  global delta + local delta + corner delta cal */
    dxl_all =dxl_global+dxl_local;
    dxw_all =dxw_global+dxw_local;

    dxl_all =dxl_all+pBSIM4Model->dxl_c;
    dxw_all =dxw_all+pBSIM4Model->dxw_c;

    /* update bin parameter */
    omi_b4_mod_bin->dlmin = omi_b4_mod_bin->dlmax = dxl_all;
    omi_b4_mod_bin->dwmin = omi_b4_mod_bin->dwmax = dxw_all;
    omi_b4_inst_value_o[B4_INST_l] = pBSIM4Inst->l;
    omi_b4_inst_value_o[B4_INST_w] = pBSIM4Inst->w;


    return OMI_OK;
  }
  else
  {
    if(prnflag==1) omiPrint(" evaltype=%d",pCKT->evalType);
    omi_b4_mod_bin->dlmin = omi_b4_mod_bin->dlmax = 0.0;
    omi_b4_mod_bin->dwmin = omi_b4_mod_bin->dwmax = 0.0;
  }


  /* global delta value cal */ 
  dxl_global =pBSIM4Model->dxl_g;
  dxw_global =pBSIM4Model->dxw_g;

  /* local delta value cal */  
  dxl_local =parl1*mis_a_1;
  dxw_local =parl2*mis_a_2;
  /**/

  /* global delta + local delta + corner delta cal */
  dxl_all =dxl_global+dxl_local;
  dxw_all =dxw_global+dxw_local;

  tox_all =tox_all+(pBSIM4Model->tox_c-pBSIM4Model->toxe);
  dxl_all =dxl_all+pBSIM4Model->dxl_c;
  dxw_all =dxw_all+pBSIM4Model->dxw_c;
  dvth_all =dvth_all+pBSIM4Model->dvth_c;
  dlvth_all =dlvth_all+pBSIM4Model->dlvth_c;
  dwvth_all =dwvth_all+pBSIM4Model->dwvth_c;
  dpvth_all =dpvth_all+pBSIM4Model->dpvth_c;
  du0_all =du0_all+pBSIM4Model->du0_c;
  dlu0_all =dlu0_all+pBSIM4Model->dlu0_c;
  dwu0_all =dwu0_all+pBSIM4Model->dwu0_c;
  dpu0_all =dpu0_all+pBSIM4Model->dpu0_c;
  dvsat_all =dvsat_all+pBSIM4Model->dvsat_c;
  dlvsat_all =dlvsat_all+pBSIM4Model->dlvsat_c;
  dwvsat_all =dwvsat_all+pBSIM4Model->dwvsat_c;
  dpvsat_all =dpvsat_all+pBSIM4Model->dpvsat_c;
  /**/

  /* default instance parameters */
  if (!pBSIM4Inst->_xwGiven)
    _xw = pBSIM4Inst->_xw = pBSIM4Model->xw+dxw_all;

  if (!pBSIM4Inst->_xlGiven)
    _xl = pBSIM4Model->xl+dxl_all;

  if (!pBSIM4Inst->adGiven)
    ad = (nf*_dmcg+_dmci)/scale*(wef/scale+_xw/scale);

  if (!pBSIM4Inst->asGiven)
    as = (nf*_dmcg+_dmci)/scale*(wef/scale+_xw/scale);

  if (!pBSIM4Inst->pdGiven)
    pd = 2*(nf*_dmcg+_dmci)/scale+(nf+1)*(wef/scale+_xw/scale);

  if (!pBSIM4Inst->psGiven)
    ps = 2*(nf*_dmcg+_dmci)/scale+(nf+1)*(wef/scale+_xw/scale);

  if (!pBSIM4Inst->nrdGiven)
    nrd = _dmcg/scale/nf/(wef/scale+_xw/scale);

  if (!pBSIM4Inst->nrsGiven)
    nrs = _dmcg/scale/nf/(wef/scale+_xw/scale);

  for(i=0;i<nf;i++)
  {
    inv_sa=inv_sa+1.0/nf/(sa*scale+(sd*scale+lef)*i+0.5*lef);
    inv_sb=inv_sb+1.0/nf/(sb*scale+(sd*scale+lef)*i+0.5*lef);
  }
  inv_saref=1.0/(saref0+0.5*lef);
  inv_sbref=1.0/(sbref0+0.5*lef);

  /* sa */
  kstress_u0=(1.0+lku00/pow((lef+_xl),llodku00)+wku00/pow((wef+_xw+wlod0),wlodku00)+pku00/pow((lef+_xl),llodku00)/pow((wef+_xw+wlod0),wlodku00))*(1+tku00*(temper/25.0-1.0));
  kstress_vth0=1.0+lkvth00/pow((lef+_xl),llodvth0)+wkvth00/pow((wef+_xw+wlod0),wlodvth0)+pkvth00/pow((lef+_xl),llodvth0)/pow((wef+_xw+wlod0),wlodvth0);
  rho_ueff=(ku00/kstress_u0)*(inv_sa+inv_sb);
  rho_ueffref=(ku00/kstress_u0)*(inv_saref+inv_sbref);

  /**/
 
  /* lod  */
  dvths_lod=(kvth00/kstress_vth0)*(inv_sa+inv_sb-inv_saref-inv_sbref);

  fu0_lod=(1.0+rho_ueff)/(1.0+rho_ueffref);

  fvsat_lod=(1.0+kvsat0*rho_ueff)/(1.0+kvsat0*rho_ueffref);

  deta0_lod=steta00*(1/pow(kstress_vth0,lodeta00))*(inv_sa+inv_sb-inv_saref-inv_sbref);

  dk2_lod=stk20*(1/pow(kstress_vth0,lodk20))*(inv_sa+inv_sb-inv_saref-inv_sbref);
  /**/  
 
  /* param=typical */
  toxe_t=pBSIM4Model->toxe;
  xl_t=pBSIM4Model->xl;
  xw_t=pBSIM4Model->xw;
  vth0_t=pBSIM4Model->vth0;
  lvth0_t=pBSIM4Model->lvth0;
  wvth0_t=pBSIM4Model->wvth0;
  pvth0_t=pBSIM4Model->pvth0;
  k2_t=pBSIM4Model->k2;
  eta0_t=pBSIM4Model->eta0;
  u0_t=pBSIM4Model->u0;
  lu0_t=pBSIM4Model->lu0;
  wu0_t=pBSIM4Model->wu0;
  pu0_t=pBSIM4Model->pu0;
  vsat_t=pBSIM4Model->vsat;
  lvsat_t=pBSIM4Model->lvsat;
  wvsat_t=pBSIM4Model->wvsat;
  pvsat_t=pBSIM4Model->pvsat;

  /* MUST inital instance/model parameter (output) value array */
  for (i = 0; i < B4_INST_SIZE_o; i++)
    omi_b4_inst_value_o[i] = OMI_AUNDEF;

  for (i = 0; i < B4_MOD_SIZE_o; i++)
    omi_b4_mod_value_o[i] = OMI_AUNDEF;

  /* set instance parameters */
  omi_b4_inst_value_o[B4_INST_l] = pBSIM4Inst->l;
  omi_b4_inst_value_o[B4_INST_w] = pBSIM4Inst->w;
  omi_b4_inst_value_o[B4_INST_m] = pBSIM4Inst->m*pBSIM4Inst->multi;
  omi_b4_inst_value_o[B4_INST_nf] = pBSIM4Inst->nf;
  omi_b4_inst_value_o[B4_INST_ad]  = pBSIM4Inst->ad= ad;
  omi_b4_inst_value_o[B4_INST_as] = pBSIM4Inst->as= as;
  omi_b4_inst_value_o[B4_INST_pd]= pBSIM4Inst->pd = pd;
  omi_b4_inst_value_o[B4_INST_ps] = pBSIM4Inst->ps= ps;
  omi_b4_inst_value_o[B4_INST_nrd] = pBSIM4Inst->nrd= nrd;
  omi_b4_inst_value_o[B4_INST_nrs] = pBSIM4Inst->nrs= nrs;
  omi_b4_inst_value_o[B4_INST_sa] = pBSIM4Inst->sa;
  omi_b4_inst_value_o[B4_INST_sb] = pBSIM4Inst->sb;
  omi_b4_inst_value_o[B4_INST_sd] = pBSIM4Inst->sd;
  omi_b4_inst_value_o[B4_INST_sca] = pBSIM4Inst->sca= sca;
  omi_b4_inst_value_o[B4_INST_scb]  = pBSIM4Inst->scb= scb;
  omi_b4_inst_value_o[B4_INST_scc] = pBSIM4Inst->scc= scc;
  omi_b4_inst_value_o[B4_INST_delvto] = pBSIM4Inst->_delvto;
  omi_b4_inst_value_o[B4_INST_mulu0] = pBSIM4Inst->_mulu0;

  /* update model parameters */
  omi_b4_mod_value_o[B4_MOD_toxe]=toxe_t+tox_all;
  omi_b4_mod_value_o[B4_MOD_xl]=xl_t+dxl_all;
  omi_b4_mod_value_o[B4_MOD_xw]=xw_t+dxw_all;
  omi_b4_mod_value_o[B4_MOD_vth0]=vth0_t+dvth_all+dvths_lod;
  omi_b4_mod_value_o[B4_MOD_lvth0]=lvth0_t+dlvth_all;
  omi_b4_mod_value_o[B4_MOD_wvth0]=wvth0_t+dwvth_all;
  omi_b4_mod_value_o[B4_MOD_pvth0]=pvth0_t+dpvth_all;
  omi_b4_mod_value_o[B4_MOD_k2]=k2_t+dk2_lod;
  omi_b4_mod_value_o[B4_MOD_eta0]=eta0_t+deta0_lod;
  omi_b4_mod_value_o[B4_MOD_u0]=(u0_t+du0_all)*fu0_lod;
  omi_b4_mod_value_o[B4_MOD_lu0]=(lu0_t+dlu0_all)*fu0_lod;
  omi_b4_mod_value_o[B4_MOD_wu0]=(wu0_t+dwu0_all)*fu0_lod;
  omi_b4_mod_value_o[B4_MOD_pu0]=(pu0_t+dpu0_all)*fu0_lod;
  omi_b4_mod_value_o[B4_MOD_vsat]=(vsat_t+dvsat_all)*fvsat_lod;
  omi_b4_mod_value_o[B4_MOD_lvsat]=(lvsat_t+dlvsat_all)*fvsat_lod;
  omi_b4_mod_value_o[B4_MOD_wvsat]=(wvsat_t+dwvsat_all)*fvsat_lod;
  omi_b4_mod_value_o[B4_MOD_pvsat]=(pvsat_t+dpvsat_all)*fvsat_lod;
  omi_b4_mod_value_o[B4_MOD_dmci]=pBSIM4Model->dmci;
  omi_b4_mod_value_o[B4_MOD_dmcg]=pBSIM4Model->dmcg;
  omi_b4_mod_value_o[B4_MOD_tnom]=pBSIM4Model->tnom;


  if(prnflag==1)
  {
    omiPrint(" Current w=%.3e",pBSIM4Inst->w);
    omiPrint(" Current l=%.3e",pBSIM4Inst->l);
    omiPrint(" Current sa=%.3e",pBSIM4Inst->sa);
    omiPrint(" Current sb=%.3e",pBSIM4Inst->sb);
    omiPrint(" Current m=%.3e",pBSIM4Inst->m);
    omiPrint(" Current multi=%.3e",pBSIM4Inst->multi);
    omiPrint(" Current scale=%.3e",pBSIM4Inst->scale);
    omiPrint(" Current _dmcg=%.3e",pBSIM4Inst->_dmcg);
    omiPrint(" Current _dmci=%.3e",pBSIM4Inst->_dmci);
    omiPrint(" Current _xw=%.3e",pBSIM4Inst->_xw);
    omiPrint(" Current _xl=%.3e",pBSIM4Inst->_xl);
    omiPrint(" Current _mulu0=%.3e",pBSIM4Inst->_mulu0);
    omiPrint(" Current prnflag=%.3e",pBSIM4Inst->prnflag);

    omiPrint(" Current parl1=%.3e",pBSIM4Model->parl1);
    omiPrint(" Current parl2=%.3e",pBSIM4Model->parl2);
    omiPrint(" Current mis_a_1=%.3e",pBSIM4Model->mis_a_1);
    omiPrint(" Current mis_a_2=%.3e",pBSIM4Model->mis_a_2);

    omiPrint(" Current saref0=%.3e",pBSIM4Model->saref0);
    omiPrint(" Current sbref0=%.3e",pBSIM4Model->sbref0);
    omiPrint(" Current wlod0=%.3e",pBSIM4Model->wlod0);
    omiPrint(" Current ku00=%.3e",pBSIM4Model->ku00);
    omiPrint(" Current lku00=%.3e",pBSIM4Model->lku00);
    omiPrint(" Current wku00=%.3e",pBSIM4Model->wku00);
    omiPrint(" Current pku00=%.3e",pBSIM4Model->pku00);
    omiPrint(" Current tku00=%.3e",pBSIM4Model->tku00);
    omiPrint(" Current llodku00=%.3e",pBSIM4Model->llodku00);
    omiPrint(" Current wlodku00=%.3e",pBSIM4Model->wlodku00);
    omiPrint(" Current kvsat0=%.3e",pBSIM4Model->kvsat0);
    omiPrint(" Current kvth00=%.3e",pBSIM4Model->kvth00);
    omiPrint(" Current lkvth00=%.3e",pBSIM4Model->lkvth00);
    omiPrint(" Current wkvth00=%.3e",pBSIM4Model->wkvth00);
    omiPrint(" Current pkvth00=%.3e",pBSIM4Model->pkvth00);
    omiPrint(" Current llodvth0=%.3e",pBSIM4Model->llodvth0);
    omiPrint(" Current wlodvth0=%.3e",pBSIM4Model->wlodvth0);
    omiPrint(" Current stk20=%.3e",pBSIM4Model->stk20);
    omiPrint(" Current lodk20=%.3e",pBSIM4Model->lodk20);
    omiPrint(" Current steta00=%.3e",pBSIM4Model->steta00);
    omiPrint(" Current lodeta00=%.3e",pBSIM4Model->lodeta00);

    omiPrint(" Current rn0xb=%.3e",pBSIM4Model->rn0xb);

    omiPrint(" Current _tcj=%.3e",pBSIM4Model->_tcj);
    omiPrint(" Current _tcjsw=%.3e",pBSIM4Model->_tcjsw);
    omiPrint(" Current _tcjswg=%.3e",pBSIM4Model->_tcjswg);
    omiPrint(" Current _tpb=%.3e",pBSIM4Model->_tpb);
    omiPrint(" Current _tpbsw=%.3e",pBSIM4Model->_tpbsw);
    omiPrint(" Current _tpbswg=%.3e",pBSIM4Model->_tpbswg);
    omiPrint(" Current _xtis=%.3e",pBSIM4Model->_xtis);
    omiPrint(" Current _njs=%.3e",pBSIM4Model->_njs);
    omiPrint(" Current _bvs=%.3e",pBSIM4Model->_bvs);
    omiPrint(" Current _mjs=%.3e",pBSIM4Model->_mjs);
    omiPrint(" Current _mjsws=%.3e",pBSIM4Model->_mjsws);
    omiPrint(" Current _mjswgs=%.3e",pBSIM4Model->_mjswgs);
    omiPrint(" Current _jss=%.3e",pBSIM4Model->_jss);
    omiPrint(" Current _jsws=%.3e",pBSIM4Model->_jsws);
    omiPrint(" Current _jswgs=%.3e",pBSIM4Model->_jswgs);
    omiPrint(" Current _jtss=%.3e",pBSIM4Model->_jtss);
    omiPrint(" Current _jtssws=%.3e",pBSIM4Model->_jtssws);
    omiPrint(" Current _jtsswgs=%.3e",pBSIM4Model->_jtsswgs);
    omiPrint(" Current _njts=%.3e",pBSIM4Model->_njts);
    omiPrint(" Current _njtssw=%.3e",pBSIM4Model->_njtssw);
    omiPrint(" Current _njtsswg=%.3e",pBSIM4Model->_njtsswg);
    omiPrint(" Current _njtsdx=%.3e",pBSIM4Model->_njtsdx);
    omiPrint(" Current _njtsswdx=%.3e",pBSIM4Model->_njtsswdx);
    omiPrint(" Current _njtsswgdx=%.3e",pBSIM4Model->_njtsswgdx);
    omiPrint(" Current _tnjts=%.3e",pBSIM4Model->_tnjts);
    omiPrint(" Current _tnjtssw=%.3e",pBSIM4Model->_tnjtssw);
    omiPrint(" Current _tnjtsswg=%.3e",pBSIM4Model->_tnjtsswg);
    omiPrint(" Current _vtss=%.3e",pBSIM4Model->_vtss);
    omiPrint(" Current _vtssws=%.3e",pBSIM4Model->_vtssws);
    omiPrint(" Current _vtsswgs=%.3e",pBSIM4Model->_vtsswgs);
    omiPrint(" Current _xtss=%.3e",pBSIM4Model->_xtss);
    omiPrint(" Current _xtssws=%.3e",pBSIM4Model->_xtssws);
    omiPrint(" Current _xtsswgs=%.3e",pBSIM4Model->_xtsswgs);
    omiPrint(" Current _pbs=%.3e",pBSIM4Model->_pbs);
    omiPrint(" Current _pbsws=%.3e",pBSIM4Model->_pbsws);
    omiPrint(" Current _pbswgs=%.3e",pBSIM4Model->_pbswgs);
    omiPrint(" Current _cjs=%.3e",pBSIM4Model->_cjs);
    omiPrint(" Current _cjsws=%.3e",pBSIM4Model->_cjsws);
    omiPrint(" Current _cjswgs=%.3e",pBSIM4Model->_cjswgs);
    omiPrint(" Current _xtid=%.3e",pBSIM4Model->_xtid);
    omiPrint(" Current _njd=%.3e",pBSIM4Model->_njd);
    omiPrint(" Current _mjd=%.3e",pBSIM4Model->_mjd);
    omiPrint(" Current _mjswd=%.3e",pBSIM4Model->_mjswd);
    omiPrint(" Current _mjswgd=%.3e",pBSIM4Model->_mjswgd);
    omiPrint(" Current _jsd=%.3e",pBSIM4Model->_jsd);
    omiPrint(" Current _jswd=%.3e",pBSIM4Model->_jswd);
    omiPrint(" Current _jswgd=%.3e",pBSIM4Model->_jswgd);
    omiPrint(" Current _jtsd=%.3e",pBSIM4Model->_jtsd);
    omiPrint(" Current _jtsswd=%.3e",pBSIM4Model->_jtsswd);
    omiPrint(" Current _jtsswgd=%.3e",pBSIM4Model->_jtsswgd);
    omiPrint(" Current _tnjtsd=%.3e",pBSIM4Model->_tnjtsd);
    omiPrint(" Current _tnjtsswd=%.3e",pBSIM4Model->_tnjtsswd);
    omiPrint(" Current _tnjtsswgd=%.3e",pBSIM4Model->_tnjtsswgd);
    omiPrint(" Current _vtsd=%.3e",pBSIM4Model->_vtsd);
    omiPrint(" Current _vtsswd=%.3e",pBSIM4Model->_vtsswd);
    omiPrint(" Current _vtsswgd=%.3e",pBSIM4Model->_vtsswgd);
    omiPrint(" Current _xtsd=%.3e",pBSIM4Model->_xtsd);
    omiPrint(" Current _xtsswd=%.3e",pBSIM4Model->_xtsswd);
    omiPrint(" Current _xtsswgd=%.3e",pBSIM4Model->_xtsswgd);
    omiPrint(" Current _pbd=%.3e",pBSIM4Model->_pbd);
    omiPrint(" Current _pbswd=%.3e",pBSIM4Model->_pbswd);
    omiPrint(" Current _pbswgd=%.3e",pBSIM4Model->_pbswgd);
    omiPrint(" Current _cjd=%.3e",pBSIM4Model->_cjd);
    omiPrint(" Current _cjswd=%.3e",pBSIM4Model->_cjswd);
    omiPrint(" Current _cjswgd=%.3e",pBSIM4Model->_cjswgd);
    omiPrint(" Current _dwj=%.3e",pBSIM4Model->_dwj);
    omiPrint(" Current _wlc=%.3e",pBSIM4Model->_wlc);
    omiPrint(" Current _wln=%.3e",pBSIM4Model->_wln);
    omiPrint(" Current _wwc=%.3e",pBSIM4Model->_wwc);
    omiPrint(" Current _wwn=%.3e",pBSIM4Model->_wwn);
    omiPrint(" Current _wwlc=%.3e",pBSIM4Model->_wwlc);

    omiPrint(" Current omimod=%.3e",pBSIM4Model->omimod);

    omiPrint(" Current agemod=%.3e",pBSIM4Model->agemod);
    omiPrint(" Current fvth0_age=%.3e",pBSIM4Model->fvth0_age);
    omiPrint(" Current dagetime=%.3e",pBSIM4Model->dagetime);
    omiPrint(" Current n_age=%.3e",pBSIM4Model->n_age);
    omiPrint(" Current Hs_age=%.3e",pBSIM4Model->Hs_age);
    omiPrint(" Current ms_age=%.3e",pBSIM4Model->ms_age);
    omiPrint(" Current Hg_age=%.3e",pBSIM4Model->Hg_age);
    omiPrint(" Current mg_age=%.3e",pBSIM4Model->mg_age);

    omiPrint(" Current Vgsdmax=%.3e",pBSIM4Model->Vgsdmax);	
	 
    omiPrint(" Current toxe=%.3e,Ori toxe=%.3e,tox_all=%.3e",omi_b4_mod_value_o[B4_MOD_toxe],pBSIM4Model->toxe,tox_all);
    omiPrint(" Current xl=%.3e,Ori xl=%.3e,dxl_all=%.3e",omi_b4_mod_value_o[B4_MOD_xl],pBSIM4Model->xl,dxl_all);
    omiPrint(" Current xw=%.3e,Ori xw=%.3e,dxw_all=%.3e",omi_b4_mod_value_o[B4_MOD_xw],pBSIM4Model->xw,dxw_all);
    omiPrint(" Current vth0=%.3e,Ori vth0=%.3e",omi_b4_mod_value_o[B4_MOD_vth0],pBSIM4Model->vth0);
    omiPrint(" Current lvth0=%.3e,Ori lvth0=%.3e",omi_b4_mod_value_o[B4_MOD_lvth0],pBSIM4Model->lvth0);
    omiPrint(" Current wvth0=%.3e,Ori wvth0=%.3e",omi_b4_mod_value_o[B4_MOD_wvth0],pBSIM4Model->wvth0);
    omiPrint(" Current pvth0=%.3e,Ori pvth0=%.3e",omi_b4_mod_value_o[B4_MOD_pvth0],pBSIM4Model->pvth0);
    omiPrint(" Current k2=%.3e,Ori k2=%.3e",omi_b4_mod_value_o[B4_MOD_k2],pBSIM4Model->k2);
    omiPrint(" Current eta0=%.3e,Ori eta0=%.3e",omi_b4_mod_value_o[B4_MOD_eta0],pBSIM4Model->eta0);
    omiPrint(" Current u0=%.3e,Ori u0=%.3e",omi_b4_mod_value_o[B4_MOD_u0],pBSIM4Model->u0);
    omiPrint(" Current lu0=%.3e,Ori lu0=%.3e",omi_b4_mod_value_o[B4_MOD_lu0],pBSIM4Model->lu0);
    omiPrint(" Current wu0=%.3e,Ori wu0=%.3e",omi_b4_mod_value_o[B4_MOD_wu0],pBSIM4Model->wu0);
    omiPrint(" Current pu0=%.3e,Ori pu0=%.3e",omi_b4_mod_value_o[B4_MOD_pu0],pBSIM4Model->pu0);
    omiPrint(" Current vsat=%.3e,Ori vsat=%.3e",omi_b4_mod_value_o[B4_MOD_vsat],pBSIM4Model->vsat);
    omiPrint(" Current lvsat=%.3e,Ori lvsat=%.3e",omi_b4_mod_value_o[B4_MOD_lvsat],pBSIM4Model->lvsat);
    omiPrint(" Current wvsat=%.3e,Ori wvsat=%.3e",omi_b4_mod_value_o[B4_MOD_wvsat],pBSIM4Model->wvsat);
    omiPrint(" Current pvsat=%.3e,Ori pvsat=%.3e",omi_b4_mod_value_o[B4_MOD_pvsat],pBSIM4Model->pvsat);
  }

 
  /* External junction diode temperature effect */
  _vt=_kb*(temper+273.15)/_q;
  _vt_tnom=_kb*(_tnom+273.15)/_q;

  _eg_tnom=1.16-(7.02e-4*(_tnom+273.15)*(_tnom+273.15))/((_tnom+273.15)+1108);
  _eg=1.16-(7.02e-4*(temper+273.15)*(temper+273.15))/((temper+273.15)+1108);

  common0=1.0-(temper+273.15)/(_tnom+273.15);
  common1=-_eg_tnom/(_kb*(temper+273.15)/_q)*common0;
  common2=temper-_tnom;
 
  weffcj=pBSIM4Inst->w/_nf+pBSIM4Inst->_xw-2*(_dwj+_wlc/pwr(pBSIM4Inst->l,_wln)+_wwc/pwr(pBSIM4Inst->w,_wwn)+_wwlc/(pwr(pBSIM4Inst->l,_wln)*pwr(pBSIM4Inst->w,_wwn))); 
  _adeff=pBSIM4Inst->ad;
  _aseff=pBSIM4Inst->as;
  _pdeff=pBSIM4Inst->pd-weffcj;
  _pseff=pBSIM4Inst->ps-weffcj;


  jtsswgs=_jtsswgs*exp(common1*_xtsswgs);
  jtssws=_jtssws*exp(common1*_xtssws);
  jtss=_jtss*exp(common1*_xtss);

  njtsswg=max((_njtsswg*(1-_tnjtsswg*common0)),0.01);
  njtssw=max((_njtssw*(1-_tnjtssw*common0)),0.01);
  njts=max((_njts*(1-_tnjts*common0)),0.01);

  pbs=max((_pbs-_tpb*common2),0.01);
  pbsws=max((_pbsws-_tpbsw*common2),0.01);
  pbswgs=max((_pbswgs-_tpbswg*common2),0.01);

  cjs=max((_cjs*(1.0+_tcj*common2)),0);
  cjsws=max((_cjsws*(1.0+_tcjsw*common2)),0);
  cjswgs=max((_cjswgs*(1.0+_tcjswg*common2)),0);

  jtsswgd=_jtsswgd*exp(common1*_xtsswgd);
  jtsswd=_jtsswd*exp(common1*_xtsswd);
  jtsd=_jtsd*exp(common1*_xtsd);

  njtsswgd=max((_njtsswgdx*(1-_tnjtsswgd*common0)),0.01);
  njtsswd=max((_njtsswdx*(1-_tnjtsswd*common0)),0.01);
  njtsd=max((_njtsdx*(1-_tnjtsd*common0)),0.01);

  pbd=max((_pbd-_tpb*common2),0.01);
  pbswd=max((_pbswd-_tpbsw*common2),0.01);
  pbswgd=max((_pbswgd-_tpbswg*common2),0.01);

  cjd=max((_cjd*(1.0+_tcj*common2)),0);
  cjswd=max((_cjswd*(1.0+_tcjsw*common2)),0);
  cjswgd=max((_cjswgd*(1.0+_tcjswg*common2)),0);

  xtis=_xtis*log((temper+273.15)/(_tnom+273.15));
  xtid=_xtid*log((temper+273.15)/(_tnom+273.15));
  
  Isbs=(_aseff*_jss+_pseff*_jsws+weffcj*_nf*_jswgs)*exp((_eg_tnom/_vt_tnom-_eg/_vt+xtis)/_njs);
  Isbd=(_adeff*_jsd+_pdeff*_jswd+weffcj*_nf*_jswgd)*exp((_eg_tnom/_vt_tnom-_eg/_vt+xtid)/_njd);

  pBSIM4Inst->_vt=_vt; pBSIM4Inst->_vt_tnom=_vt_tnom; pBSIM4Inst->_eg_tnom=_eg_tnom; pBSIM4Inst->_eg=_eg; pBSIM4Inst->common0=common0; pBSIM4Inst->common1=common1; pBSIM4Inst->common2=common2; 
  pBSIM4Inst->weffcj=weffcj; pBSIM4Inst->_adeff=_adeff; pBSIM4Inst->_aseff=_aseff; pBSIM4Inst->_pdeff=_pdeff; pBSIM4Inst->_pseff=_pseff ;
  pBSIM4Inst->jtsswgs=jtsswgs; pBSIM4Inst->jtssws=jtssws; pBSIM4Inst->jtss=jtss; pBSIM4Inst->njtsswg=njtsswg; pBSIM4Inst->njtssw=njtssw; pBSIM4Inst->njts=njts; pBSIM4Inst->Isbs=Isbs; 
  pBSIM4Inst->pbs=pbs; pBSIM4Inst->pbsws=pbsws; pBSIM4Inst->pbswgs=pbswgs; pBSIM4Inst->cjs=cjs; pBSIM4Inst->cjsws=cjsws; pBSIM4Inst->cjswgs=cjswgs; 
  pBSIM4Inst->jtsswgd=jtsswgd; pBSIM4Inst->jtsswd=jtsswd; pBSIM4Inst->jtsd=jtsd; pBSIM4Inst->njtsswgd=njtsswgd; pBSIM4Inst->njtsswd=njtsswd; pBSIM4Inst->njtsd=njtsd; pBSIM4Inst->Isbd=Isbd; 
  pBSIM4Inst->pbd=pbd; pBSIM4Inst->pbswd=pbswd; pBSIM4Inst->pbswgd=pbswgd; pBSIM4Inst->cjd=cjd; pBSIM4Inst->cjswd=cjswd; pBSIM4Inst->cjswgd=cjswgd; 
  pBSIM4Inst->xtis=xtis; pBSIM4Inst->xtid=xtid;


  if ( pCKT->omiAge == 1)	/* option to turn on aging flow */
  {
    void *pSimpleAge = NULL;

    if (! strlen(omiAgeInfoPath) )
    {
      pBSIM4Inst->instName = strdup (pBSIM4Inst->instName);
      pSimpleAge = (void *) malloc (sizeof(omiSimpleAge));

      memset (pSimpleAge, 0, sizeof(omiSimpleAge));
      if (! pHashTableAge)
      {
        if (pCKT->tblSize == 0)
          i = 128 * 2048;    /* default */
        else
          i = pCKT->tblSize;

        pHashTableAge = omiHashCreate(i, omiFreeElem);
      }
      omiHashEnter (pHashTableAge, pBSIM4Inst->instName, pSimpleAge);
      pBSIM4Inst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      pBSIM4Inst->pSimpleAge->modelNameId = OMI_MOS_BSIM4;
    }
    else if (pHashTableAge)
    {      
      pSimpleAge = omiHashFind (pHashTableAge, pBSIM4Inst->instName);
      pBSIM4Inst->pSimpleAge = (omiSimpleAge *) pSimpleAge;

      if (pSimpleAge) /*it has value*/
      {
        if((iret=omiBSIM4ExtraploateAge (pBSIM4Model, pBSIM4Inst)) == OMI_ERROR)
        {
          OMI_status=OMI_ERROR;
          return OMI_ERROR;
        }
        omiBSIM4DegradeAge (pBSIM4Model, pBSIM4Inst);
      }
    }

    return OMI_AGE;
  }

  return OMI_OK;
}

int omiBSIM4CheckModel (omiInstance *pInstance, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst)
{
  return OMI_OK;
}

static
int omiBSIM4ExtraploateAge (omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIM4Inst->pSimpleAge;
  double Ta_c = pBSIM4Model->dagetime;
  double tran_time=0;

  tran_time = pSimpleAge->tran_time;  
  if(pSimpleAge->extrapolate_flag==0)
  {
    if(tran_time>0) pSimpleAge->Age = pSimpleAge->Age + pSimpleAge->dAge * Ta_c * yr_to_sec / tran_time;
  
    omiDagetime=pBSIM4Model->dagetime; /* save relative age time */
  }    
  pSimpleAge->extrapolate_flag=1;
  return OMI_OK;
}

static
int omiBSIM4DegradeAge (omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst)
{
  omiSimpleAge *pSimpleAge = (omiSimpleAge *) pBSIM4Inst->pSimpleAge;
  double n = pBSIM4Model->n_age;

  omi_b4_mod_value_o[B4_MOD_vth0] += pBSIM4Model->fvth0_age * pow( pSimpleAge->Age, n);
  
  return OMI_OK;
}


/* end of $RCSfile: omiBSIM4Temp.c,v $ */
