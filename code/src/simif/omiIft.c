/*
****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiIft.c 
 *  Date        : 2019_0730
 *  Description : To return OMI IFT
 */


#include <stdio.h>
#include <string.h>
#include "omiDef.h"
#include "omiIft.h"
#include "omiHash.h"
#include "omiAge.h"


/* OMI create function */
extern char *omiBSIM4Create (void *pModelData);
extern char *omiPSPCreate (void *pModelData);
extern char *omiHiSIMHVCreate (void *pModelData);
extern char *omiBSIMCMGCreate (void *pModelData);
extern char *omiHiSIM2Create (void *pModelData);
extern char *omiBSIMSOICreate (void *pModelData);
extern char *omiBSIMIMGCreate (void *pModelData);
extern char *omiBSIMBULKCreate (void *pModelData);
extern char *omiASMCreate (void *pModelData);
extern char *omiMVSGCreate (void *pModelData);
extern char *omiLUTSOICreate (void *pModelData);

char *omiCreate (int spiceType, int id, int level, void *pModelData)
{
  if (id == OMI_MOS_BSIM4)
    return omiBSIM4Create (pModelData);
  if (id == OMI_MOS_PSP)
    return omiPSPCreate (pModelData);
  if (id == OMI_MOS_HiSIMHV)
    return omiHiSIMHVCreate (pModelData);
  if (id == OMI_MOS_BSIMCMG)
    return omiBSIMCMGCreate (pModelData);
  if (id == OMI_MOS_HiSIM2)
    return omiHiSIM2Create (pModelData);
  if (id == OMI_MOS_BSIMSOI)
    return omiBSIMSOICreate (pModelData);
  if (id == OMI_MOS_BSIMIMG)
    return omiBSIMIMGCreate (pModelData);
  if (id == OMI_MOS_BSIMBULK)
    return omiBSIMBULKCreate (pModelData);
  if (id == OMI_MOS_ASM)
    return omiASMCreate (pModelData);
  if (id == OMI_MOS_MVSG)
    return omiMVSGCreate (pModelData);
  if (id == OMI_MOS_LUTSOI)
    return omiLUTSOICreate (pModelData);

  return NULL;
}


int omiPrintAge (omiCKT *pCKT)
{
  char *instName = NULL;
  void *pAge = NULL;
  pElement p = NULL;
  FILE *omiOutput = NULL;
  FILE *omiDefFile = NULL;
  int  printAgeTime = 1;
  omiSimpleAge *pSimpleAge = NULL;
  int  nameLen = 0, ageSize = 0;
  FILE* cfgFile = NULL;
  char tempFileName[512];

  if( OMI_status==OMI_ERROR )  return OMI_ERROR;
  if (pCKT->degFile != NULL)
  {
    if ((omiDefFile = fopen (pCKT->degFile, "w")) == NULL)
      omiPrint("OMI cannot open %s", pCKT->degFile);
    else
    {
      fprintf (omiDefFile, "** OMI degradation **\n\n");

      while (omiHashGet (pHashTableAge, &instName, &pAge, &p))
      {
          pSimpleAge = (omiSimpleAge *)pAge;

          if (pCKT->omiSort)
          /* skip: sort pAge by pCKT->omiSort */;

          if (printAgeTime)
          {
            fprintf (omiDefFile, "dageTime     = %.13e yr\n", omiDagetime);
            fprintf (omiDefFile, "Sum dageTime = %.13e yr\n\n\n", pSimpleAge->agetime + omiDagetime);
            printAgeTime = 0;
          }

          fprintf (omiDefFile, "%s\n", instName);
          fprintf (omiDefFile, "Age       = %.13e\n",  pSimpleAge->Age);
            
          pSimpleAge->agetime = pSimpleAge->agetime + omiDagetime; /*accumulate previous dagetime*/
      }
      fclose (omiDefFile);
    }
    strcpy(omiAgeInfoPath,"no matter what it is");
  }

  instName = NULL;
  pAge = NULL;
  p = NULL;
  
  /* write binary file */
  if (pCKT->omiOutput != NULL && pCKT->omiSave == 1)
  {
    if((cfgFile = fopen(pCKT->omiOutput,"w")) == NULL )
      omiPrint("OMI cannot open %s", pCKT->omiOutput);
    else
    {
      fprintf(cfgFile,"age_data_file\t1\t%s.dat\n",pCKT->omiOutput);
      fclose(cfgFile);
      sprintf(tempFileName,"%s.dat",pCKT->omiOutput);
    }
    
    if ((omiOutput = fopen (tempFileName, "wb")) == NULL)
      omiPrint("OMI cannot open %s", tempFileName);
    else
    {
      while (omiHashGet (pHashTableAge, &instName, &pAge, &p))
      {
        nameLen = strlen(instName);

        ageSize = sizeof(omiSimpleAge);
        putw (nameLen, omiOutput);
        fwrite (instName, nameLen, 1, omiOutput);
        putw (ageSize, omiOutput);
        fwrite (pAge, ageSize, 1, omiOutput);
      }
      fclose (omiOutput);
    }
    strcpy(omiAgeInfoPath,tempFileName);
  }
  
  omiFreeAgeFlag = 0;
  return OMI_OK;
}


int omiFreeAge()
{
  omiHashDestroy (pHashTableAge);
  pHashTableAge = NULL;

  return OMI_OK;
}


/* end of $RCSfile: omiIft.c,v $ */
