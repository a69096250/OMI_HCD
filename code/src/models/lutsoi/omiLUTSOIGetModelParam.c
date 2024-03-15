/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiLUTSOIGetModelParam.c
 *  Date        : 2020_0420
 *  Description : To get model parameters
 */


#include "omiLUTSOIDef.h"


ParamId omiLUTSOIGetModelParamIdByName (String aName)
{
  return omiGetNode(omiLUTSOIModelHeader, aName);
}

  
/* end of $RCSfile: omiLUTSOIGetModelParam.c,v $ */
