/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4InitInstParam.c
 *  Date        : 2010_1123
 *  Description : To initialize instance parameters
 */


#include "omiBSIM4Def.h"


int omiBSIM4InitInstParam (omiBSIM4Instance *pBSIM4Inst)
{
  /* BSIM4 instance parameters */
  pBSIM4Inst->lGiven = 0;
  pBSIM4Inst->wGiven = 0;
  pBSIM4Inst->mGiven = 0;
  pBSIM4Inst->nfGiven = 0;
  pBSIM4Inst->adGiven = 0;
  pBSIM4Inst->asGiven = 0;
  pBSIM4Inst->pdGiven = 0;
  pBSIM4Inst->psGiven = 0;
  pBSIM4Inst->nrdGiven = 0;
  pBSIM4Inst->nrsGiven = 0;
  pBSIM4Inst->saGiven = 0;
  pBSIM4Inst->sbGiven = 0;
  pBSIM4Inst->sdGiven = 0;
  pBSIM4Inst->scaGiven = 0;
  pBSIM4Inst->scbGiven = 0;
  pBSIM4Inst->sccGiven = 0;
  pBSIM4Inst->delvtoGiven = 0;
  pBSIM4Inst->mulu0Given = 0;

  /* Flexible instance parameters */
  pBSIM4Inst->multiGiven=0,pBSIM4Inst->scaleGiven=0,pBSIM4Inst->_dmcgGiven=0,pBSIM4Inst->_dmciGiven=0,pBSIM4Inst->_xwGiven=0;
  pBSIM4Inst->_xlGiven=0,pBSIM4Inst->_delvtoGiven=0,pBSIM4Inst->_mulu0Given=0,pBSIM4Inst->prnflagGiven=0;

  return OMI_OK;
}

  
/* end of $RCSfile: omiBSIM4InitInstParam.c,v $ */
