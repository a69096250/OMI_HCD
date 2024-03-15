/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiAge.h 
 *  Date        : 2010_1123
 *  Description : OMI age structures
 */


#ifndef  OMIAGE_H
#define  OMIAGE_H


#define yr_to_sec 365*24*60*60


extern pHashTable pHashTableAge;
extern double omiDagetime;
extern char   omiAgeInfoPath[512];
extern int    OMI_status;          /* pass OMI_OK or OMI_ERROR to omiPrintAge */
extern int    omiGetCfgFlag;
extern int    omiFreeAgeFlag;


typedef struct omiAgeData
{
  /* standard model information, must be 1st field */
  int    modelNameId;		/* model name id */
} omiAgeData;

typedef struct omiSimpleAge
{
  /* standard model information, must be 1st field */
  int    modelNameId;		/* model name id */

  /* customized aging information */
  double agetime;
  double Age;
  double dAge;
  double tran_time;
  int extrapolate_flag;
  /*HCD aging Information*/
  double dVth;
  double dVth_extra;
  double t_deg;
} omiSimpleAge;

typedef omiSimpleAge omiBSIMCMGAge;
typedef omiSimpleAge omiHiSIM2Age;
typedef omiSimpleAge omiBSIMSOIAge;
#endif /* OMIAGE_H */


/* end of $RCSfile: omiAge.h,v $ */
