/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiASMGetModelParam.c
 *  Date        : 2019_0726
 *  Description : To get model parameters
 */


#include "omiASMDef.h"


ParamId omiASMGetModelParamIdByName (String aName)
{
  return omiGetNode(omiASMModelHeader, aName);
}

  
/* end of $RCSfile: omiASMGetModelParam.c,v $ */
