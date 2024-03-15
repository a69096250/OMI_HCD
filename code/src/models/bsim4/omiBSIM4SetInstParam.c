/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4SetInstParam.c
 *  Date        : 2010_1123
 *  Description : To get instance parameter values
 */


#include "omiBSIM4Def.h"


int omiBSIM4SetInstParam (omiBSIM4Instance *pBSIM4Inst, String aName, double aValue)
{
  switch(omiBSIM4GetInstParamIdByName(aName))
  {
    case B4_INST_l:
      pBSIM4Inst->l = aValue;
      pBSIM4Inst->lGiven = TRUE;
      break;
    case B4_INST_w:
      pBSIM4Inst->w = aValue;
      pBSIM4Inst->wGiven = TRUE;
      break;
    case B4_INST_m:
      pBSIM4Inst->m = aValue;
      pBSIM4Inst->mGiven = TRUE;
      break;
    case B4_INST_nf:
      pBSIM4Inst->nf = aValue;
      pBSIM4Inst->nfGiven = TRUE;
      break;
    case B4_INST_ad:
      pBSIM4Inst->ad = aValue;
      pBSIM4Inst->adGiven = TRUE;
      break;
    case B4_INST_as:
      pBSIM4Inst->as = aValue;
      pBSIM4Inst->asGiven = TRUE;
      break;
    case B4_INST_pd:
      pBSIM4Inst->pd = aValue;
      pBSIM4Inst->pdGiven = TRUE;
      break;
    case B4_INST_ps:
      pBSIM4Inst->ps = aValue;
      pBSIM4Inst->psGiven = TRUE;
      break;
    case B4_INST_nrd:
      pBSIM4Inst->nrd = aValue;
      pBSIM4Inst->nrdGiven = TRUE;
      break;
    case B4_INST_nrs:
      pBSIM4Inst->nrs = aValue;
      pBSIM4Inst->nrsGiven = TRUE;
      break;
    case B4_INST_sa:
      pBSIM4Inst->sa = aValue;
      pBSIM4Inst->saGiven = TRUE;
      break;
    case B4_INST_sb:
      pBSIM4Inst->sb = aValue;
      pBSIM4Inst->sbGiven = TRUE;
      break;
    case B4_INST_sd:
      pBSIM4Inst->sd = aValue;
      pBSIM4Inst->sdGiven = TRUE;
      break;
    case B4_INST_sca:
      pBSIM4Inst->sca = aValue;
      pBSIM4Inst->scaGiven = TRUE;
      break;
    case B4_INST_scb:
      pBSIM4Inst->scb = aValue;
      pBSIM4Inst->scbGiven = TRUE;
      break;
    case B4_INST_scc:
      pBSIM4Inst->scc = aValue;
      pBSIM4Inst->sccGiven = TRUE;
      break;
    case B4_INST_delvto:
      pBSIM4Inst->delvto = aValue;
      pBSIM4Inst->delvtoGiven = TRUE;
      break;
    case B4_INST_mulu0:
      pBSIM4Inst->mulu0 = aValue;
      pBSIM4Inst->mulu0Given = TRUE;
      break;

    case B4_INST_multi:
      pBSIM4Inst->multi = aValue;
      pBSIM4Inst->multiGiven = TRUE;
      break;

    case B4_INST_scale:
      pBSIM4Inst->scale = aValue;
      pBSIM4Inst->scaleGiven = TRUE;
      break;

    case B4_INST__dmcg:
      pBSIM4Inst->_dmcg = aValue;
      pBSIM4Inst->_dmcgGiven = TRUE;
      break;

    case B4_INST__dmci:
      pBSIM4Inst->_dmci = aValue;
      pBSIM4Inst->_dmciGiven = TRUE;
      break;

    case B4_INST__xw:
      pBSIM4Inst->_xw = aValue;
      pBSIM4Inst->_xwGiven = TRUE;
      break;

    case B4_INST__xl:
      pBSIM4Inst->_xl = aValue;
      pBSIM4Inst->_xlGiven = TRUE;
      break;

    case B4_INST__delvto:
      pBSIM4Inst->_delvto = aValue;
      pBSIM4Inst->_delvtoGiven = TRUE;
      break;

    case B4_INST__mulu0:
      pBSIM4Inst->_mulu0 = aValue;
      pBSIM4Inst->_mulu0Given = TRUE;
      break;

    case B4_INST_prnflag:
      pBSIM4Inst->prnflag = aValue;
      pBSIM4Inst->prnflagGiven = TRUE;
      break;

    default:
      break;
  }

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4SetInstParam.c,v $ */
