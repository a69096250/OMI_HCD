/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Eval.c
 *  Date        : 2010_1123
 *  Description : BSIM4 model evaluation
 */


#include <math.h>
#include "omiBSIM4Def.h"
#include "omiBSIM4Ift.h"

#define sgn(A) (A>0 ? 1:( A<0 ? -1:0))


/* The following code uses the topology after omiBSIM4SetTopology() */
/* This is the evaluation function */
int
omiBSIM4Evaluate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIM4Model    *pBSIM4Model = (omiBSIM4Model    *) pModelData;
  omiBSIM4Instance *pBSIM4Inst  = (omiBSIM4Instance *) pInstData;
  omiBSIM4WorkData *pBSIM4WorkData = (omiBSIM4WorkData *) pEvalData->workData;
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;
  /* get node voltage */
  double Vxd = pBSIM4WorkData->V[map[omiBSIM4xd]];
  /* Vxg is not used
  double Vxg = pBSIM4WorkData->V[map[omiBSIM4xg]];*/
  double Vxs = pBSIM4WorkData->V[map[omiBSIM4xs]];
  /* Vxb is not used 
  double Vxb = pBSIM4WorkData->V[map[omiBSIM4xb]];*/
  /* Vid, Vis are not used 
  double Vid = pBSIM4WorkData->V[map[omiBSIM4id]];
  double Vis = pBSIM4WorkData->V[map[omiBSIM4is]];*/
  double Vn0 = pBSIM4WorkData->V[map[omiBSIM4n0]];
  
  double _type=0;

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

  double _gmin=pEvalData->gmin;
  double  _q=1.609e-19;
  double _kb=1.3806226e-23;
  double _tnom=pBSIM4Model->tnom;
  double _nf=pBSIM4Inst->nf;
  
  double _vt=pBSIM4Inst->_vt, _vt_tnom=pBSIM4Inst->_vt_tnom, _eg_tnom=pBSIM4Inst->_eg_tnom, _eg=pBSIM4Inst->_eg, common0=pBSIM4Inst->common0, common1=pBSIM4Inst->common1, common2=pBSIM4Inst->common2;
  double weffcj =pBSIM4Inst->weffcj, _adeff =pBSIM4Inst->_adeff, _aseff =pBSIM4Inst->_aseff, _pdeff =pBSIM4Inst->_pdeff, _pseff =pBSIM4Inst->_pseff ;
  double jtsswgs=pBSIM4Inst->jtsswgs, jtssws=pBSIM4Inst->jtssws, jtss=pBSIM4Inst->jtss, njtsswg=pBSIM4Inst->njtsswg, njtssw=pBSIM4Inst->njtssw, njts=pBSIM4Inst->njts, Isbs=pBSIM4Inst->Isbs;
  double pbs=pBSIM4Inst->pbs, pbsws=pBSIM4Inst->pbsws, pbswgs=pBSIM4Inst->pbswgs, cjs=pBSIM4Inst->cjs, cjsws=pBSIM4Inst->cjsws, cjswgs=pBSIM4Inst->cjswgs; 
  double jtsswgd=pBSIM4Inst->jtsswgd, jtsswd=pBSIM4Inst->jtsswd, jtsd=pBSIM4Inst->jtsd, njtsswgd=pBSIM4Inst->njtsswgd, njtsswd=pBSIM4Inst->njtsswd, njtsd=pBSIM4Inst->njtsd, Isbd=pBSIM4Inst->Isbd;
  double pbd=pBSIM4Inst->pbd, pbswd=pBSIM4Inst->pbswd, pbswgd=pBSIM4Inst->pbswgd, cjd=pBSIM4Inst->cjd, cjswd=pBSIM4Inst->cjswd, cjswgd=pBSIM4Inst->cjswgd;
  double xtis=pBSIM4Inst->xtis, xtid=pBSIM4Inst->xtid;

  double max_vbc =0, max_cur =0, E =0, G =0, H =0;          
  double A1 =0, B1 =0,     dB1 =0,     term1 =0, In0xd1 =0, In0xd1_n0xd =0;
  double A2 =0, B2 =0, C2 =0, D2 =0, dB2 =0, dC2 =0, dD2 =0, term2 =0, In0xd2 =0, In0xd2_n0xd =0;
  double A3 =0, B3 =0, C3 =0, D3 =0, dB3 =0, dC3 =0, dD3 =0, term3 =0, In0xd3 =0, In0xd3_n0xd =0;
  double A4 =0, B4 =0, C4 =0, D4 =0, dB4 =0, dC4 =0, dD4 =0, term4 =0, In0xd4 =0, In0xd4_n0xd =0;
  double A5 =0, B5 =0,     dB5 =0,     term5 =0, In0xs5 =0, In0xs5_n0xs =0;
  double A6 =0, B6 =0, C6 =0, D6 =0, dB6 =0, dC6 =0, dD6 =0, term6 =0, In0xs6 =0, In0xs6_n0xs =0;
  double A7 =0, B7 =0, C7 =0, D7 =0, dB7 =0, dC7 =0, dD7 =0, term7 =0, In0xs7 =0, In0xs7_n0xs =0;
  double A8 =0, B8 =0, C8 =0, D8 =0, dB8 =0, dC8 =0, dD8 =0, term8 =0, In0xs8 =0, In0xs8_n0xs =0;

  double Cn0xd=0;
  double Cn0xs=0;
  double M0=0, M1=0, M2=0, M3=0, M4=0;
  double N0=0, N1=0, N2=0, N3=0, N4=0;

if (pEvalData->evalI == omiEvalTopo || pEvalData->evalQ == omiEvalTopo)
{
  /* Rn0xb simulates as constant resistance in this sample */
  if (pBSIM4Model->rn0xb != 0.0)
    pBSIM4SpecData->Gn0xb = 1.0 / pBSIM4Model->rn0xb;
  else
    pBSIM4SpecData->Gn0xb = 0.0;

  return OMI_OK;
}

if ( !(pEvalData->evalI == omiEvalNothing && pEvalData->evalQ == omiEvalNothing) )
{

  if(pBSIM4Model->modelType==NMOS)
  {
      _type=1;
  }
  if(pBSIM4Model->modelType==PMOS)
  {
      _type=-1;
  }
  
  max_vbc=1.0e3;
  max_cur=0.08;

  E=_type*max_cur;
  G=_gmin*_type*(Vn0-Vxd);
  H=_gmin*_type*(Vn0-Vxs);

  A1=_type*Isbd;
  B1=_type*(Vn0-Vxd)/(_njd*_vt);
  dB1=_type/(_njd*_vt);
  term1=A1*(exp(B1)-1.0);
  In0xd1=G+0.5*(term1+E-_type*sqrt((term1-E)*(term1-E) + 1e-15));
  In0xd1_n0xd=_gmin*_type+0.5*(1-_type*(term1-E)/sqrt((term1-E)*(term1-E) + 1e-15))*(A1*exp(B1)*dB1);
  
  A2=_type*weffcj*_nf*jtsswgd;
  B2=_type*(-1)*(Vn0-Vxd)/(njtsswgd*_vt_tnom)  *0.5;
  C2=_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd)) + max_vbc;
  D2=sqrt( (_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd)) - max_vbc)+ 1e-6 );
  dB2=_type*(-1)/(njtsswgd*_vt_tnom)  *0.5;
  dC2=(-1)*_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd))/(_vtsswgd+_type*(-1)*(Vn0-Vxd))*_type*(-1);
  dD2=0.5/sqrt( (_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsswgd/(_vtsswgd+_type*(-1)*(Vn0-Vxd)) - max_vbc) + 1e-6 )*2*(C2-2*max_vbc)*dC2;
  term2=A2*(exp(B2*(C2-D2))-1.0);
  In0xd2=G-0.5*(term2+E-_type*sqrt((term2-E)*(term2-E) + 1e-15));
  In0xd2_n0xd=_gmin*_type-0.5*(1-_type*(term2-E)/sqrt((term2-E)*(term2-E) + 1e-15))*(A2*exp(B2*(C2-D2))*(dB2*(C2-D2)+B2*(dC2-dD2)));

  A3=_type*_pdeff    *jtsswd;
  B3=_type*(-1)*(Vn0-Vxd)/(njtsswd*_vt_tnom)  *0.5;
  C3=_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd)) + max_vbc;
  D3=sqrt( (_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd)) - max_vbc) + 1e-6 );
  dB3=_type*(-1)/(njtsswd*_vt_tnom)  *0.5;
  dC3=(-1)*_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd))/(_vtsswd+_type*(-1)*(Vn0-Vxd))*_type*(-1);
  dD3=0.5/sqrt( (_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsswd/(_vtsswd+_type*(-1)*(Vn0-Vxd)) - max_vbc) + 1e-6 )*2*(C3-2*max_vbc)*dC3;
  term3=A3*(exp(B3*(C3-D3))-1.0);
  In0xd3=G-0.5*(term3+E-_type*sqrt((term3-E)*(term3-E) + 1e-15));
  In0xd3_n0xd=_gmin*_type-0.5*(1-_type*(term3-E)/sqrt((term3-E)*(term3-E) + 1e-15))*(A3*exp(B3*(C3-D3))*(dB3*(C3-D3)+B3*(dC3-dD3)));

  A4=_type*_adeff    *jtsd;
  B4=_type*(-1)*(Vn0-Vxd)/(njtsd*_vt_tnom)  *0.5;
  C4=_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd)) + max_vbc;
  D4=sqrt( (_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd)) - max_vbc) + 1e-6 );
  dB4=_type*(-1)/(njtsd*_vt_tnom)  *0.5;
  dC4=(-1)*_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd))/(_vtsd+_type*(-1)*(Vn0-Vxd))*_type*(-1);
  dD4=0.5/sqrt( (_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd)) - max_vbc)*(_vtsd/(_vtsd+_type*(-1)*(Vn0-Vxd)) - max_vbc) + 1e-6 )*2*(C4-2*max_vbc)*dC4;
  term4=A4*(exp(B4*(C4-D4))-1.0);
  In0xd4=G-0.5*(term4+E-_type*sqrt((term4-E)*(term4-E) + 1e-15));
  In0xd4_n0xd=_gmin*_type-0.5*(1-_type*(term4-E)/sqrt((term4-E)*(term4-E) + 1e-15))*(A4*exp(B4*(C4-D4))*(dB4*(C4-D4)+B4*(dC4-dD4)));

  A5=_type*Isbs;
  B5=_type*(Vn0-Vxs)/(_njs*_vt);
  dB5=_type/(_njs*_vt);
  term5=A5*(exp(B5)-1.0);
  In0xs5=H+0.5*(term5+E-_type*sqrt((term5-E)*(term5-E) + 1e-15));
  In0xs5_n0xs=_gmin*_type+0.5*(1-_type*(term5-E)/sqrt((term5-E)*(term5-E) + 1e-15))*(A5*exp(B5)*dB5);

  A6=_type*weffcj*_nf*jtsswgs;
  B6=_type*(-1)*(Vn0-Vxs)/(njtsswg*_vt_tnom)  *0.5;
  C6=_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs)) + max_vbc;
  D6=sqrt( (_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 );
  dB6=_type*(-1)/(njtsswg*_vt_tnom)  *0.5;
  dC6=(-1)*_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs))/(_vtsswgs+_type*(-1)*(Vn0-Vxs))*_type*(-1);
  dD6=0.5/sqrt( (_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtsswgs/(_vtsswgs+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 )*2*(C6-2*max_vbc)*dC6;
  term6=A6*(exp(B6*(C6-D6))-1.0);
  In0xs6=H-0.5*(term6+E-_type*sqrt((term6-E)*(term6-E) + 1e-15));
  In0xs6_n0xs=_gmin*_type-0.5*(1-_type*(term6-E)/sqrt((term6-E)*(term6-E) + 1e-15))*(A6*exp(B6*(C6-D6))*(dB6*(C6-D6)+B6*(dC6-dD6)));
  
  A7=_type*_pseff    *jtssws;
  B7=_type*(-1)*(Vn0-Vxs)/(njtssw*_vt_tnom)  *0.5;
  C7=_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs)) + max_vbc;
  D7=sqrt( (_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 );
  dB7=_type*(-1)/(njtssw*_vt_tnom)  *0.5;
  dC7=(-1)*_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs))/(_vtssws+_type*(-1)*(Vn0-Vxs))*_type*(-1);
  dD7=0.5/sqrt( (_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtssws/(_vtssws+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 )*2*(C7-2*max_vbc)*dC7;
  term7=A7*(exp(B7*(C7-D7))-1.0);
  In0xs7=H-0.5*(term7+E-_type*sqrt((term7-E)*(term7-E) + 1e-15));
  In0xs7_n0xs=_gmin*_type-0.5*(1-_type*(term7-E)/sqrt((term7-E)*(term7-E) + 1e-15))*(A7*exp(B7*(C7-D7))*(dB7*(C7-D7)+B7*(dC7-dD7)));

  A8=_type*_aseff    *jtss;
  B8=_type*(-1)*(Vn0-Vxs)/(njts*_vt_tnom)  *0.5;
  C8=_vtss/(_vtss+_type*(-1)*(Vn0-Vxs)) + max_vbc;
  D8=sqrt( (_vtss/(_vtss+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtss/(_vtss+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 );
  dB8=_type*(-1)/(njts*_vt_tnom)  *0.5;
  dC8=(-1)*_vtss/(_vtss+_type*(-1)*(Vn0-Vxs))/(_vtss+_type*(-1)*(Vn0-Vxs))*_type*(-1);
  dD8=0.5/sqrt( (_vtss/(_vtss+_type*(-1)*(Vn0-Vxs)) - max_vbc)*(_vtss/(_vtss+_type*(-1)*(Vn0-Vxs)) - max_vbc) + 1e-6 )*2*(C8-2*max_vbc)*dC8;
  term8=A8*(exp(B8*(C8-D8))-1.0);
  In0xs8=H-0.5*(term8+E-_type*sqrt((term8-E)*(term8-E) + 1e-15));
  In0xs8_n0xs=_gmin*_type-0.5*(1-_type*(term8-E)/sqrt((term8-E)*(term8-E) + 1e-15))*(A8*exp(B8*(C8-D8))*(dB8*(C8-D8)+B8*(dC8-dD8)));

  /* model evaluation and save evaluation result to workData */
  /* Rn0xb simulates as constant resistance in this sample */
  if (pBSIM4Model->rn0xb != 0.0)
    pBSIM4SpecData->Gn0xb = 1.0 / pBSIM4Model->rn0xb;
  else
    pBSIM4SpecData->Gn0xb = 0.0;

  /* I, dI/dV evaluation */ 
  pBSIM4WorkData->In0xd = In0xd1+In0xd2+In0xd3+In0xd4;
  pBSIM4WorkData->In0xd_n0xd = In0xd1_n0xd+In0xd2_n0xd+In0xd3_n0xd+In0xd4_n0xd;
 
  pBSIM4WorkData->In0xs = In0xs5+In0xs6+In0xs7+In0xs8;
  pBSIM4WorkData->In0xs_n0xs = In0xs5_n0xs+In0xs6_n0xs+In0xs7_n0xs+In0xs8_n0xs;

  /* Q, dQ/dV evaluation */
  M0=(1.0-_type*sgn(Vn0-Vxd))/2.0;
  M1=(1.0+_type*sgn(Vn0-Vxd))/2.0;
  M2=_type/pbswgd;
  M3=_type/pbd;
  M4=_type/pbswd;
  Cn0xd=weffcj*_nf*cjswgd*(M0*pwr((1.0-M0*M2*(Vn0-Vxd)),-1*_mjswgd)+M1*(1+_mjswgd*M2*(Vn0-Vxd)))	+_adeff*cjd*       (M0*pwr((1.0-M0*M3*(Vn0-Vxd)   ),-1*_mjd   )+M1*(1+_mjd*M3*(Vn0-Vxd)))	+_pdeff*cjswd*     (M0*pwr((1.0-M0*M4*(Vn0-Vxd)),-1*_mjswd  )+M1*(1+_mjswd*M4*(Vn0-Vxd)));

  N0=(1.0-_type*sgn(Vn0-Vxs))/2.0;
  N1=(1.0+_type*sgn(Vn0-Vxs))/2.0;
  N2=_type/pbswgs;
  N3=_type/pbs;
  N4=_type/pbsws;
  Cn0xs=weffcj*_nf*cjswgs*(N0*pwr((1.0-N0*N2*(Vn0-Vxs)),-1*_mjswgs)+N1*(1+_mjswgs*N2*(Vn0-Vxs)))	+_aseff*cjs*       (N0*pwr((1.0-N0*N3*(Vn0-Vxs)   ),-1*_mjs   )+N1*(1+_mjs*N3*(Vn0-Vxs)))	+_pseff*cjsws*     (N0*pwr((1.0-N0*N4*(Vn0-Vxs)),-1*_mjsws  )+N1*(1+_mjsws*N4*(Vn0-Vxs)));

  pBSIM4WorkData->Qn0xd = (weffcj*_nf*cjswgd*(M0*(pwr((1.0-M0*M2*(Vn0-Vxd)),-1*_mjswgd+1)-1)/(-1*_mjswgd+1)/(-1*M0*M2+1e-20)+M1*((Vn0-Vxd)+_mjswgd/2*M2*(Vn0-Vxd)*(Vn0-Vxd)))+_adeff*cjd*(M0*(pwr((1.0-M0*M3*(Vn0-Vxd)),-1*_mjd+1)-1)/(-1*_mjd+1)/(-1*M0*M3+1e-20)+M1*((Vn0-Vxd)+_mjd/2*M3*(Vn0-Vxd)*(Vn0-Vxd)))+_pdeff*cjswd*(M0*(pwr((1.0-M0*M4*(Vn0-Vxd)),-1*_mjswd+1)-1)/(-1*_mjswd+1)/(-1*M0*M4+1e-20)+M1*((Vn0-Vxd)+_mjswd/2*M4*(Vn0-Vxd)*(Vn0-Vxd))));
  pBSIM4WorkData->Qn0xd_n0xd = Cn0xd;

  pBSIM4WorkData->Qn0xs =  (weffcj*_nf*cjswgs*(N0*(pwr((1.0-N0*N2*(Vn0-Vxs)),-1*_mjswgs+1)-1)/(-1*_mjswgs+1)/(-1*N0*N2+1e-20)+N1*((Vn0-Vxs)+_mjswgs/2*N2*(Vn0-Vxs)*(Vn0-Vxs)))+_aseff*cjs*(N0*(pwr((1.0-N0*N3*(Vn0-Vxs)),-1*_mjs+1)-1)/(-1*_mjs+1)/(-1*N0*N3+1e-20)+N1*((Vn0-Vxs)+_mjs/2*N3*(Vn0-Vxs)*(Vn0-Vxs)))+_pseff*cjsws*(N0*(pwr((1.0-N0*N4*(Vn0-Vxs)),-1*_mjsws+1)-1)/(-1*_mjsws+1)/(-1*N0*N4+1e-20)+N1*((Vn0-Vxs)+_mjsws/2*N4*(Vn0-Vxs)*(Vn0-Vxs))));
  pBSIM4WorkData->Qn0xs_n0xs = Cn0xs;

} /* pEvalData->evalI != omiEvalNothing */

  return OMI_OK;
}


/* This is noise evaluation function */
int
omiBSIM4Noise (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIM4Model    *pBSIM4Model = (omiBSIM4Model    *) pModelData;
  omiBSIM4Instance *pBSIM4Inst  = (omiBSIM4Instance *) pInstData;
  omiBSIM4WorkData *pBSIM4WorkData = (omiBSIM4WorkData *) pEvalData->workData;
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  omiNoiseData *pBSIM4NoiseData = (omiNoiseData *) pEvalData->noiseData;
  int *map = pBSIM4SpecData->map;
  /* get node voltage */
  double Vxd = pBSIM4WorkData->V[map[omiBSIM4xd]];
  double Vxg = pBSIM4WorkData->V[map[omiBSIM4xg]];
  double Vxs = pBSIM4WorkData->V[map[omiBSIM4xs]];
  double Vxb = pBSIM4WorkData->V[map[omiBSIM4xb]];
  double Vid = pBSIM4WorkData->V[map[omiBSIM4id]];
  double Vis = pBSIM4WorkData->V[map[omiBSIM4is]];
  double Vn0 = pBSIM4WorkData->V[map[omiBSIM4n0]];

  /* noise evaluation and save evaluation result to noiseData */
  /* 1st noise: thermal, between n0 and xb  */
  pBSIM4NoiseData[0].name = "thermal";
  pBSIM4NoiseData[0].value = 1e-15*pBSIM4Model->rn0xb;
  pBSIM4NoiseData[0].term1 = pBSIM4SpecData->node[map[omiBSIM4n0]];
  pBSIM4NoiseData[0].term2 = pBSIM4SpecData->node[map[omiBSIM4xb]];
  /* 2nd noise: flicker, between n0 and xb */
  pBSIM4NoiseData[1].name = "flicker";
  pBSIM4NoiseData[1].value = 1e-25*pBSIM4Model->rn0xb/pEvalData->freq;
  pBSIM4NoiseData[1].term1 = pBSIM4SpecData->node[map[omiBSIM4n0]];
  pBSIM4NoiseData[1].term2 = pBSIM4SpecData->node[map[omiBSIM4xb]];  
  
  return OMI_OK;
}


/* end of $RCSfile: omiBSIM4Eval.c,v $ */
