/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIM4GetModelParam.c
 *  Date        : 2019_0726
 *  Description : To get model parameters
 */


#include "omiBSIM4Def.h"


ParamId omiBSIM4GetModelParamIdByName (String aName)
{
  return omiGetNode(omiBSIM4ModelHeader, aName);
}

  
/* end of $RCSfile: omiBSIM4GetModelParam.c,v $ */
