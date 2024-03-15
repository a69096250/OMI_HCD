/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Ift.c
 *  Date        : 2010_1123
 *  Description : BSIM4 functions in IFT
 */


#include <math.h>
#include "omiBSIM4Def.h"
#include "omiBSIM4Ift.h"


/* This is node mapping function */
static int
omiBSIM4SetTopology (omiEvalData *pEvalData, int *stdNode, int *newNode)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;
  int i, index;
  int tmpNode;

  /* save node number to specData */
  for (i = 0; i < OMI_BSIM4_STD_NODE_SIZE_MAX; i++)
    pBSIM4SpecData->node[i] = stdNode[i];

  for (i = 0; i < pBSIM4SpecData->newNodeSize; i++)
    pBSIM4SpecData->node[OMI_BSIM4_STD_NODE_SIZE_MAX + i] = newNode[i];

  /* if pBSIM4SpecData->newNodeSize < OMI_BSIM4_NEW_NODE_SIZE_MAX (some new nodes are merged),
     simulators will only pass nodes and voltages of pBSIM4SpecData->newNodeSize to OMI,
     but OMI code may use nodes and voltages of OMI_BSIM4_NEW_NODE_SIZE_MAX. So map is needed */
  for (i = 0; i < OMI_BSIM4_STD_NODE_SIZE_MAX + OMI_BSIM4_NEW_NODE_SIZE_MAX; i++)
    map[i] = i;

  index = 0;
  /* n0 is real body of standard BSIM4, xb is represented as body in netlist */
  if (pBSIM4SpecData->Gn0xb == 0.0)
    /* n0, xb are same one node */
    map[omiBSIM4n0] = map[omiBSIM4xb];
  else if (index < pBSIM4SpecData->newNodeSize)
  {
    /* n0, xb need to be exchanged */
    tmpNode = stdNode[omiBSIM4xb];
    /* other nodes and xb may be same one node, then need to be exchanged accordingly */
    if (stdNode[omiBSIM4ib] == stdNode[omiBSIM4xb])
    { 
      if (stdNode[omiBSIM4db] == stdNode[omiBSIM4ib]) 
      {
        stdNode[omiBSIM4db] = newNode[index];
      }
      if (stdNode[omiBSIM4sb] == stdNode[omiBSIM4ib]) 
      {
        stdNode[omiBSIM4sb] = newNode[index];
      }
      stdNode[omiBSIM4ib] = newNode[index];		
    }  
    /* n0, xb are exchanged */
    stdNode[omiBSIM4xb] = newNode[index];          
    newNode[index] = tmpNode;
 
  }

  index++;
  /* if index < pBSIM4SpecData->newNodeSize, other nodes may need to be exchanged too */

  return OMI_OK;
}


/* This function returns number of new node */
static int
omiBSIM4TermCount (omiEvalData *pEvalData)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  pBSIM4SpecData->newNodeSize = 0;

  if (pBSIM4SpecData->Gn0xb != 0.0)
  {
    pBSIM4SpecData->newNodeSize++;	/* new node n0 */
  }

  return pBSIM4SpecData->newNodeSize;
}


/* This function returns number of all constant conductances */
static omiNodeType
omiBSIM4TerminalType(omiEvalData *pEvalData, int term_index)
{
  /* 2 new nodes:
     0 - new node n0,
     1 - BR  node n1 */
  if (term_index == 1)
    return omiNodeTypeFlow;
  else
    return omiNodeTypePotential;
}


/* The following code uses the topology after omiBSIM4SetTopology() */
/* This function returns number of all constant conductances */
static int
omiBSIM4ConstCondCount (omiEvalData *pEvalData)
{
  return 1;		/* Gn0xb */
}


/* This function returns row of "dindex" constant conductance */
static int
omiBSIM4ConstCondRow (omiEvalData *pEvalData, int dindex, int in_out)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (dindex)
  {
    case 0:		/* Gn0xb */
      if (in_out == 0)
        return pBSIM4SpecData->node[map[omiBSIM4xb]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns column of "dindex" constant conductance */
static int
omiBSIM4ConstCondColumn (omiEvalData *pEvalData, int dindex, int plus_minus)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (dindex)
  {
    case 0:		/* Gn0xb */
      if (plus_minus == 0)
        return pBSIM4SpecData->node[map[omiBSIM4xb]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns value of "dindex" constant conductance */
static double
omiBSIM4ConstCondValue (omiEvalData *pEvalData, int dindex)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;

  switch (dindex)
  {
    case 0:		/* Gn0xb */
      return  pBSIM4SpecData->Gn0xb;
    default:
      break;
  }

  return 0;
}


/* This function returns number of all currents */
static int
omiBSIM4ISize (omiEvalData *pEvalData)
{
  return 2;		/* In0xd, In0xs */
}


/* This function returns row of "rhs_index" current */
static int
omiBSIM4ITermRow (omiEvalData *pEvalData, int rhs_index, int in_out)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (rhs_index)
  {
    case 0:		 /* In0xd */
      if (in_out == 0)
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4xd]];
    case 1:		 /* In0xs */
      if (in_out == 0)
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4xs]];
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns offset of "rhs_index" current */
static int
omiBSIM4IWorkDataOffset (omiEvalData *pEvalData, int rhs_index)
{
  switch (rhs_index)
  {
    case 0:		 /* In0xd */
      return OMI_BSIM4_WORK_DATA_OFFSET(In0xd);
    case 1:		 /* In0xs */
      return OMI_BSIM4_WORK_DATA_OFFSET(In0xs);
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns number of "rhs_index" current's all derivatives */
static int
omiBSIM4IderivSize (omiEvalData *pEvalData, int rhs_index)
{
  switch (rhs_index)
  {
    case 0:		 /* In0xd_n0xd */
      return 1;
    case 1:		 /* In0xs_n0xs */
      return 1;
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns offset of "rhs_index" current's "deriv_index" derivative */
static int
omiBSIM4IderivWorkDataOffset (omiEvalData *pEvalData, int rhs_index, int deriv_index)
{
  switch (rhs_index)
  {
    case 0:		 /* In0xd */
      switch (deriv_index)
      {
        case 0:		/* In0xd_n0xd */
          return OMI_BSIM4_WORK_DATA_OFFSET(In0xd_n0xd);
        default:
          break;
      }
    case 1:		 /* In0xs */
      switch (deriv_index)
      {
        case 0:		/* In0xs_n0xs */
          return OMI_BSIM4_WORK_DATA_OFFSET(In0xs_n0xs);
        default:
          break;
      }
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns column of "rhs_index" current's "deriv_index" derivative */
static int
omiBSIM4IderivTermCol (omiEvalData *pEvalData, int rhs_index, int deriv_index, int plus_minus)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (rhs_index)
  {
    case 0:		 /* In0xd */
      switch (deriv_index)
      {
        case 0:		/* In0xd_n0xd */
          if (plus_minus == 0)
            return pBSIM4SpecData->node[map[omiBSIM4n0]];
          else
            return pBSIM4SpecData->node[map[omiBSIM4xd]];
        default:
          break;
      }
    case 1:		 /* In0xs */
      switch (deriv_index)
      {
        case 0:		/* In0xs_n0xs */
          if (plus_minus == 0)
            return pBSIM4SpecData->node[map[omiBSIM4n0]];
          else
            return pBSIM4SpecData->node[map[omiBSIM4xs]];
        default:
          break;
      }
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns number of all charges */
static int
omiBSIM4QSize (omiEvalData *pEvalData)
{
  return 2;		/* Qn0xd, Qn0xs */
}


/* This function returns row of "rhs_index" charge */
static int
omiBSIM4QTermRow (omiEvalData *pEvalData, int rhs_index, int in_out)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (rhs_index)
  {
    case 0:		/* Qn0xd */
      if (in_out == 0)
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4xd]];
    case 1:		/* Qn0xs */
      if (in_out == 0)
        return pBSIM4SpecData->node[map[omiBSIM4n0]];
      else
        return pBSIM4SpecData->node[map[omiBSIM4xs]];
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns offset of "rhs_index" charge */
static int
omiBSIM4QWorkDataOffset (omiEvalData *pEvalData, int rhs_index)
{
  switch (rhs_index)
  {
    case 0:		/* Qn0xd */
      return OMI_BSIM4_WORK_DATA_OFFSET(Qn0xd);
    case 1:		/* Qn0xs */
      return OMI_BSIM4_WORK_DATA_OFFSET(Qn0xs);
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns number of "rhs_index" charge's all derivatives */
static int
omiBSIM4QderivSize (omiEvalData *pEvalData, int rhs_index)
{
  switch (rhs_index)
  {
    case 0:		/* Qn0xd_n0xd */
      return 1;
    case 1:		/* Qn0xs_n0xs */
      return 1;
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns offset of "rhs_index" charge's "deriv_index" derivative */
static int
omiBSIM4QderivWorkDataOffset (omiEvalData *pEvalData, int rhs_index, int deriv_index)
{
  switch (rhs_index)
  {
    case 0:		/* Qn0xd */
      switch (deriv_index)
      {
        case 0:		/* Qn0xd_n0xd */
          return OMI_BSIM4_WORK_DATA_OFFSET(Qn0xd_n0xd);
        default:
          break;
      }
    case 1:		/* Qn0xs */
      switch (deriv_index)
      {
        case 0:		/* Qn0xs_n0xs */
          return OMI_BSIM4_WORK_DATA_OFFSET(Qn0xs_n0xs);
        default:
          break;
      }
    default:
      break;
  }

  return OMI_DEFAULT;
}


/* This function returns column of "rhs_index" charge's "deriv_index" derivative */
static int
omiBSIM4QderivTermCol (omiEvalData *pEvalData, int rhs_index, int deriv_index, int plus_minus)
{
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;

  switch (rhs_index)
  {
    case 0:		/* Qn0xd */
      switch (deriv_index)
      {
        case 0:		/* Qn0xd_n0xd */
          if (plus_minus == 0)
            return pBSIM4SpecData->node[map[omiBSIM4n0]];
          else
            return pBSIM4SpecData->node[map[omiBSIM4xd]];
        default:
          break;
      }
    case 1:		/* Qn0xs */
      switch (deriv_index)
      {
        case 0:		/* Qn0xs_n0xs */
          if (plus_minus == 0)
            return pBSIM4SpecData->node[map[omiBSIM4n0]];
          else
            return pBSIM4SpecData->node[map[omiBSIM4xs]];
        default:
          break;
      }
    default:
      break;
  }

  return OMI_DEFAULT;
}


static int
omiBSIM4InitdAge (omiBSIM4Model *pBSIM4Model, omiSimpleAge *pSimpleAge)
{
  pSimpleAge->dAge = 0.0;
  pSimpleAge->tran_time = 0.0;
  pSimpleAge->extrapolate_flag = 0;

  return OMI_OK;
}


static int
omiBSIM4Integrate (void *pModelData, void *pInstData, omiEvalData *pEvalData)
{
  omiBSIM4Model *pBSIM4Model = (omiBSIM4Model *) pModelData;
  omiBSIM4Instance *pBSIM4Inst = (omiBSIM4Instance *) pInstData;

  omiSimpleAge *pSimpleAge = pBSIM4Inst->pSimpleAge;
  omiBSIM4CoreData *pBSIM4CoreData = pEvalData->coreData;
  omiBSIM4WorkData *pBSIM4WorkData = (omiBSIM4WorkData *) pEvalData->workData;
  omiBSIM4SpecData *pBSIM4SpecData = (omiBSIM4SpecData *) pEvalData->specData;
  int *map = pBSIM4SpecData->map;
  double Ids = pBSIM4CoreData->ids, Isub = pBSIM4CoreData->isub;
  double Ig = pBSIM4CoreData->igso + pBSIM4CoreData->igdo + pBSIM4CoreData->igb + pBSIM4CoreData->igcs + pBSIM4CoreData->igcd;
  double W = pBSIM4Inst->w;
  double Hs = pBSIM4Model->Hs_age, ms = pBSIM4Model->ms_age;
  double Hg = pBSIM4Model->Hg_age, mg = pBSIM4Model->mg_age;

  double Vxd = pBSIM4WorkData->V[map[omiBSIM4xd]];
  double Vxg = pBSIM4WorkData->V[map[omiBSIM4xg]];
  double Vxs = pBSIM4WorkData->V[map[omiBSIM4xs]];
  double Vxb = pBSIM4WorkData->V[map[omiBSIM4xb]];
  double step = pEvalData->step;
  /* Not used 
  double time = pEvalData->time;*/
  double temp;
			
  if (pBSIM4Model->modelType == NMOS)
  {
    if( Vxd < Vxs )
    {
      temp=Vxd;
      Vxd=Vxs;
      Vxs=temp;
    }
    Vxd=Vxd-Vxs;
    Vxg=Vxg-Vxs;
    Vxb=Vxb-Vxs;
  }
  else
  {
    if( Vxd > Vxs )
    {
      temp=Vxd;
      Vxd=Vxs;
      Vxs=temp;
    }
    Vxd=-1*(Vxd-Vxs);
    Vxg=-1*(Vxg-Vxs);
    Vxb=-1*(Vxb-Vxs);
  }
	
  /* SOA warning */
  if( fabs(Vxg - Vxd) > pBSIM4Model->Vgsdmax )
    omiPrint("\n  **Warning** Vgd (= %f ) of %s setting has exceeded Vgsdmax (= %f )",Vxg - Vxd, pBSIM4Inst->instName ,pBSIM4Model->Vgsdmax);
  if( fabs(Vxg - Vxs) > pBSIM4Model->Vgsdmax )
    omiPrint("\n  **Warning** Vgs (= %f ) of %s setting has exceeded Vgsdmax (= %f )",Vxg - Vxs, pBSIM4Inst->instName ,pBSIM4Model->Vgsdmax);

  if (!pBSIM4Inst->pSimpleAge)
    return OMI_OK;

  if (pEvalData->time == 0.0)
  {
    omiBSIM4InitdAge (pBSIM4Model, pBSIM4Inst->pSimpleAge);
  }
  else
  {
    /* evaluate dAge (defined by customer) */
    if (pBSIM4Model->agemod == 1)
    {
      pSimpleAge->dAge += (Ids / (W * Hs)) * pow ((Isub / Ids), ms) * step;
    }
    else
    {
      pSimpleAge->dAge += (1.0 / Hg) * pow ((fabs(Ig) / W), mg) * step;
    }
    pSimpleAge->tran_time += step;		
  }
  return OMI_OK;
}


/* This structure defines BSIM4 IFT */
static omiIft omiBSIM4Ift =
{
/*omiBSIM4Update*/
  sizeof(omiBSIM4WorkData),
  sizeof(omiBSIM4SpecData),
  0,                                    /* probeDataSize */
  2,                                    /* noiseDataSize */
  omiBSIM4Evaluate,
  NULL,                                 /* omiNoise */
  omiBSIM4SetTopology,
  omiBSIM4TermCount,
  omiBSIM4TerminalType,                 /* omiTerminalType */
  omiBSIM4ConstCondCount,
  omiBSIM4ConstCondRow,
  omiBSIM4ConstCondColumn,
  omiBSIM4ConstCondValue,
  omiBSIM4ISize,
  omiBSIM4ITermRow,
  omiBSIM4IWorkDataOffset,
  omiBSIM4IderivSize,
  omiBSIM4IderivWorkDataOffset,
  omiBSIM4IderivTermCol,
  omiBSIM4QSize,
  omiBSIM4QTermRow,
  omiBSIM4QWorkDataOffset,
  omiBSIM4QderivSize,
  omiBSIM4QderivWorkDataOffset,
  omiBSIM4QderivTermCol,
  omiBSIM4Integrate,
};

static omiIft omiBSIM4Ift1 =
{
/*omiBSIM4Update*/
  sizeof(omiBSIM4WorkData),
  sizeof(omiBSIM4SpecData),
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
  omiBSIM4Integrate,
};

static omiIft omiBSIM4Ift2 =
{
/*omiBSIM4Update*/
  sizeof(omiBSIM4WorkData),
  sizeof(omiBSIM4SpecData),
  0,                                    /* probeDataSize */
  2,                                    /* noiseDataSize */
  omiBSIM4Evaluate,
  NULL,                                 /* omiNoise */
  omiBSIM4SetTopology,
  omiBSIM4TermCount,
  omiBSIM4TerminalType,                 /* omiTerminalType */
  omiBSIM4ConstCondCount,
  omiBSIM4ConstCondRow,
  omiBSIM4ConstCondColumn,
  omiBSIM4ConstCondValue,
  omiBSIM4ISize,
  omiBSIM4ITermRow,
  omiBSIM4IWorkDataOffset,
  omiBSIM4IderivSize,
  omiBSIM4IderivWorkDataOffset,
  omiBSIM4IderivTermCol,
  omiBSIM4QSize,
  omiBSIM4QTermRow,
  omiBSIM4QWorkDataOffset,
  omiBSIM4QderivSize,
  omiBSIM4QderivWorkDataOffset,
  omiBSIM4QderivTermCol,
  NULL,
};

/* This function returns the pointer of OMI IFT to simulator */
char *
omiBSIM4Create (void *pModelData)
{
  omiBSIM4Model *pBSIM4Model = (omiBSIM4Model *) pModelData;

  if (fabs(pBSIM4Model->omimod)<1e-3)
    return NULL;
  else if (fabs(pBSIM4Model->omimod-1)<1e-3)
    return (char *)&omiBSIM4Ift1;
  else if (fabs(pBSIM4Model->omimod-2)<1e-3)
    return (char *)&omiBSIM4Ift2;
  else
    return (char *)&omiBSIM4Ift;
}
 

/* end of $RCSfile: omiBSIM4Ift.c,v $ */
