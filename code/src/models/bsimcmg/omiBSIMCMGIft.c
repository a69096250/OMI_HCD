/*
 ***************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ***************************************************************************
 *  File        : omiBSIMCMGIft.c
 *  Date        : 2019_0726
 *  Description : BSIMCMG functions in IFT
 */


#include <math.h>
#include "omiBSIMCMGDef.h"
#include "omiBSIMCMGIft.h"




static int
omiBSIMCMGInitdAge (omiBSIMCMGModel *pBSIMCMGModel, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;
  pSimpleAge->dVth = 0.0;
  pSimpleAge->t_deg = 0.0;
  return OMI_OK;
}


static int
omiBSIMCMGIntegrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIMCMGModel *pBSIMCMGModel = (omiBSIMCMGModel *) pModelData;
  omiBSIMCMGInstance *pBSIMCMGInst = (omiBSIMCMGInstance *) pInstData;

  omiSimpleAge *pSimpleAge = pBSIMCMGInst->pSimpleAge;
  omiBSIMCMGCoreData *pBSIMCMGCoreData = pEvalData->coreData;
  omiBSIMCMGWorkData *pBSIMCMGWorkData = (omiBSIMCMGWorkData *) pEvalData->workData;
  omiBSIMCMGSpecData *pBSIMCMGSpecData = (omiBSIMCMGSpecData *) pEvalData->specData;

  double step = pEvalData->step;
  int *map = pBSIMCMGSpecData->map;
  double temp;
  double devsign;
  /*HCD compact model params*/
  double a0 = pBSIMCMGModel->a0;
  double b0 = pBSIMCMGModel->b0;
  double c0 = pBSIMCMGModel->c0;
  double ea0 = pBSIMCMGModel->ea0;
  double d0 = pBSIMCMGModel->d0;
  double nox = pBSIMCMGModel->nox;
  double kB = 1.3806e-23;
  double q = 1.602e-19;
  double Tsimu=273.15 + pBSIMCMGModel->tsimu;// Unit: K
  double dVth = 0.0;//dVth of HCD
  double dVth_former = 0.0;//dVth at former time step
  double teff = 0.0;//effective time
  double AR = 0.0;//aging rate of HCD
  omiPrint("step=%e,time=%e",step,pSimpleAge->tran_time);
  /*HCD Voltage*/
  double Vxd=pBSIMCMGWorkData->V[omiBSIMCMGxd];
  double Vxg=pBSIMCMGWorkData->V[omiBSIMCMGxg];
  double Vxs=pBSIMCMGWorkData->V[omiBSIMCMGxs];
  double Vxb=pBSIMCMGWorkData->V[omiBSIMCMGxe];
  
    if (pBSIMCMGModel->modelType == NMOS)
    {
        if (Vxd < Vxs)
        {
            temp = Vxd;
            Vxd = Vxs;
            Vxs = temp;
        }
        Vxd = Vxd - Vxs;
        Vxg = Vxg - Vxs;
        Vxb = Vxb - Vxs;
        devsign = 1.0;
    }
    else
    {
        if (Vxd > Vxs)
        {
            temp = Vxd;
            Vxd = Vxs;
            Vxs = temp;
        }
        Vxd = -1 * (Vxd - Vxs);
        Vxg = -1 * (Vxg - Vxs);
        Vxb = -1 * (Vxb - Vxs);
        devsign = -1.0;
    }

  if (!pBSIMCMGInst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiBSIMCMGInitdAge (pBSIMCMGModel, pBSIMCMGInst->pSimpleAge);
  }
  else
  {
    if (abs(Vxd-0)>1e-3 || abs(Vxg-0)>1e-3)
    {
      /* evaluate dAge (defined by customer) */
      dVth_former = pBSIMCMGInst->pSimpleAge->dVth;
      AR=a0*pow((Vxg-0.15),b0)*exp(-c0/(Vxd-0.27))*exp(-ea0*q/(kB*Tsimu));
      teff=pow((exp(dVth_former/AR)-1)/d0,1/nox);
      pBSIMCMGInst->pSimpleAge->dVth=AR*log(1+d0*pow(teff+step,nox));
      pSimpleAge->t_deg += step;
    }else{//No degradation at zero bias 
      pBSIMCMGInst->pSimpleAge->dVth += 0.0;
    }
    omiPrint("dVth = %e, teff = %e,tdeg=%e",pBSIMCMGInst->pSimpleAge->dVth,teff,pSimpleAge->t_deg);
    pSimpleAge->tran_time += step;
  }
  return OMI_OK;
}


/* This structure defines BSIMCMG IFT */
static omiIft omiBSIMCMGIft =
{
/*omiBSIMCMGUpdate*/
  sizeof(omiBSIMCMGWorkData),
  sizeof(omiBSIMCMGSpecData),
  0,                                    /* probeDataSize */
  2,                                    /* noiseDataSize */
  NULL,
  NULL,                                 /* omiNoise */
  NULL,
  NULL,
  NULL,                                 /* omiTerminalType */
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  omiBSIMCMGIntegrate,
};



/* This function returns the pointer of OMI IFT to simulator */
char *
omiBSIMCMGCreate (void *pModelData)
{
  omiBSIMCMGModel *pBSIMCMGModel = (omiBSIMCMGModel *) pModelData;

  if (fabs(pBSIMCMGModel->omimod)<1e-3)
    return NULL;
  else if (fabs(pBSIMCMGModel->omimod-1)<1e-3)
    return (char *)&omiBSIMCMGIft;
  else {
    omiPrint("OMIMOD parameter was specified as %d.",(int)pBSIMCMGModel->omimod);
    omiPrint("As of OMI version 1.1.0, OMIMOD may only be 0 or 1.");
    omiPrint("Proceeding as if OMIMOD is 0.");
    return NULL;
  }
}
 

/* end of $RCSfile: omiBSIMCMGIft.c,v $ */
