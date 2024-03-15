/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : tmiWrapper.c 
 *  Date        : 2017-02-28
 *  Description : Wrapper to offer OMI routines through TMI
 */


#include "omiDef.h"
#include "omiIft.h"


int tmiUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance)
{
  return omiUpdate (pCKT, pModel, pInstance);
}

char *tmiCreate (int spiceType, int id, int level, void *pModelData)
{
  return omiCreate (spiceType, id, level, pModelData);
}

int tmiPrintAge (omiCKT *pCKT)
{
  return omiPrintAge (pCKT);
}

int tmiFreeAge()
{
  return omiFreeAge ();
}
