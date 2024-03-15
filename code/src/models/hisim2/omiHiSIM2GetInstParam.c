/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiHiSIM2GetInstParam.c
 *  Date        : 2019_0726
 *  Description : To get instance parameters
 */


#include <string.h>
#include "omiHiSIM2Def.h"


ParamId omiHiSIM2GetInstParamIdByName (String aName)
{
  /* Only first 8 characters are used for compare */
  char word[10];

  if(strlen(aName)<=8)
    return omiGetNode(omiHiSIM2InstHeader, aName);
  else
  {
    strncpy(word,aName,8);
    word[8]='\0';
    return omiGetNode(omiHiSIM2InstHeader, word);
  }
}

  
/* end of $RCSfile: omiHiSIM2GetInstParam.c,v $ */
