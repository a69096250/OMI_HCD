/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiIft.h 
 *  Date        : 2016-11-22
 *  Description : OMI IFT and related structures
 */


#ifndef  OMIIFT_H
#define  OMIIFT_H


#define OMI_DEFAULT -1

/* This macro gets workData offset of a field */
#define OMI_WORK_DATA_OFFSET(_type_, _field_) \
(&((_type_ *) 0)->_field_ - (double *) 0)

#define OMI_BSIM4_STD_NODE_SIZE_MAX 12/* maximum BSIM4 standard node size */


/* This enumerates all of BSIM4 standard nodes */
typedef enum omiBSIM4StdNode
{
  omiBSIM4id,           /* 0, internal drain */
  omiBSIM4xg,           /* 1, external gate */
  omiBSIM4is,           /* 2, internal source */
  omiBSIM4xb,           /* 3, external body */
  omiBSIM4xd,           /* 4, external drain */
  omiBSIM4xs,           /* 5, external source */
  omiBSIM4ig,           /* 6, internal gate, when rgatemod > 0 */
  omiBSIM4mg,           /* 7, middle gate, when rgatemod > 1 */
  omiBSIM4ib,           /* 8, internal body, when rbodymod > 0 */
  omiBSIM4db,           /* 9, internal drain side body, when rbodymod > 0 */
  omiBSIM4sb,           /* 10, internal source side body, when rbodymod > 0 */
  omiBSIM4nqs           /* 11, non-quasi-static node, when nqsmod > 0 */
} omiBSIM4StdNode;

#define OMI_BSIMCMG_STD_NODE_SIZE_MAX 19/* maximum BSIMCMG standard node size */


/* This enumerates all of BSIMCMG standard nodes */


/* This code proposed by YCLiangb of TSMC on 2014-07-30 */
typedef enum omiBSIMCMGStdNode
{
  omiBSIMCMGid,           /* 0, internal drain, when rdsmod > 0 */
  omiBSIMCMGxg,           /* 1, external gate */
  omiBSIMCMGis,           /* 2, internal source, when rdsmod > 0 */
  omiBSIMCMGxe,           /* 3, external body */
  omiBSIMCMGxd,           /* 4, external drain */
  omiBSIMCMGxs,           /* 5, external source */
  omiBSIMCMGge,           /* 6, internal gate, when rgatemod > 0 */
  omiBSIMCMGtnode,        /* 7, self-heating node, when shmod >0 and rth0 > 0 */
  omiBSIMCMGgi,           /* 8, non-quasi-static node, when nqsmod = 1 */
  omiBSIMCMGq,            /* 9, non-quasi-static node, when nqsmod = 2 */
  omiBSIMCMGq1,           /* 10, non-quasi-static node, when nqsmod = 3, nseg >= 4 */
  omiBSIMCMGq2,           /* 11, non-quasi-static node, when nqsmod = 3, nseg >= 4 */
  omiBSIMCMGq3,           /* 12, non-quasi-static node, when nqsmod = 3, nseg >= 4 */
  omiBSIMCMGq4,           /* 13, non-quasi-static node, when nqsmod = 3, nseg >= 5 */
  omiBSIMCMGq5,           /* 14, non-quasi-static node, when nqsmod = 3, nseg >= 6 */
  omiBSIMCMGq6,           /* 15, non-quasi-static node, when nqsmod = 3, nseg >= 7 */
  omiBSIMCMGq7,           /* 16, non-quasi-static node, when nqsmod = 3, nseg >= 8 */
  omiBSIMCMGq8,           /* 17, non-quasi-static node, when nqsmod = 3, nseg >= 9 */
  omiBSIMCMGq9,           /* 18, non-quasi-static node, when nqsmod = 3, nseg >= 10 */
} omiBSIMCMGStdNode;

/* begin: for HiSIM2 (Renesas, 2015/6) */
#define OMI_HiSIM2_STD_NODE_SIZE_MAX 10/* maximum HiSIM2 standard node size */


/* This enumerates all of HiSIM2 standard nodes */
typedef enum omiHiSIM2StdNode
{
  omiHiSIM2xd,           /* 0, external drain */
  omiHiSIM2xg,           /* 1, external gate */
  omiHiSIM2xs,           /* 2, external source */
  omiHiSIM2xb,           /* 3, external body */
  omiHiSIM2id,           /* 4, internal drain, when corsrd < 0 */
  omiHiSIM2ig,           /* 5, internal gate, when coreg == 1 */
  omiHiSIM2is,           /* 6, internal source, when corsrd < 0 */
  omiHiSIM2ib,           /* 7, internal body, when corbnet == 1 */
  omiHiSIM2db,           /* 8, internal drain side body, when corbnet == 1 */
  omiHiSIM2sb,           /* 9, internal source side body, when corbnet == 1 */
} omiHiSIM2StdNode;
/* end:   for HiSIM2 (Renesas, 2015/6) */

/* begin: for BSIMSOI (TSMC, 2015/3) */
#define OMI_BSIMSOI_STD_NODE_SIZE_MAX 13/* maximum BSIMSOI standard node size */

/* This enumerates all of BSIMSOI standard nodes */
typedef enum omiBSIMSOIStdNode
{
  omiBSIMSOId,           /* 0, external drain */
  omiBSIMSOIg,           /* 1, external gate */
  omiBSIMSOIs,           /* 2, external source */
  omiBSIMSOIe,           /* 3, external substrate */
  omiBSIMSOIp,           /* 4, external body contact */
  omiBSIMSOIdi,          /* 5, internal drain */
  omiBSIMSOIsi,          /* 6, internal source */
  omiBSIMSOIgi,          /* 7, internal gate */
  omiBSIMSOIgm,          /* 8, middle gate */
  omiBSIMSOIb,           /* 9, internal body */
  omiBSIMSOIsb,          /* 10, internal source side body */
  omiBSIMSOIdb,          /* 11, internal drain side body */
  omiBSIMSOIt            /* 12, self-heating node */
} omiBSIMSOIStdNode;
/* end: for BSIMSOI (TSMC, 2015/3) */

/* begin: for BSIMIMG (W. Rhett Davis, 2018/8) */
#define OMI_BSIMIMG_STD_NODE_SIZE_MAX 9 /* maximum BSIMIMG standard node size */

/* This enumerates all of BSIMIMG standard nodes */
typedef enum omiBSIMIMGStdNode
{
  omiBSIMIMGd,           /* 0, external drain */
  omiBSIMIMGfg,          /* 1, external front-gate */
  omiBSIMIMGs,           /* 2, external source */
  omiBSIMIMGbg,          /* 3, external back-gate */
  omiBSIMIMGdi,          /* 4, internal drain */
  omiBSIMIMGsi,          /* 5, internal source */
  omiBSIMIMGgi,          /* 6, internal gate */
  omiBSIMIMGge,          /* 7, gate edge */
  omiBSIMIMGt            /* 8, self-heating node */
} omiBSIMIMGStdNode;
/* end: for BSIMIMG (W. Rhett Davis, 2018/8) */

/* begin: for BSIMBULK (W. Rhett Davis, 2019/9) */
#define OMI_BSIMBULK_STD_NODE_SIZE_MAX 14 /* maximum BSIMBULK standard node size */

/* This enumerates all of BSIMBULK standard nodes */
typedef enum omiBSIMBULKStdNode
{
  omiBSIMBULKd,       /* 0, external drain */
  omiBSIMBULKg,       /* 1, external gate */
  omiBSIMBULKs,       /* 2, external source */
  omiBSIMBULKb,       /* 3, external body */
  omiBSIMBULKdi,      /* 4, internal drain */
  omiBSIMBULKsi,      /* 5, internal source */
  omiBSIMBULKgi,      /* 6, internal gate */
  omiBSIMBULKgm,      /* 7, middle gate, when rgatemod = 3 */
  omiBSIMBULKbi,      /* 8, internal body */
  omiBSIMBULKsbulk,   /* 9, internal source side body, when rbodymod > 0 */
  omiBSIMBULKdbulk,   /* 10, internal drain side body, when rbodymod > 0 */
  omiBSIMBULKn1,      /* 11, correlated drain & gate noise node 1, when rnoimod = 1 */
  omiBSIMBULKn2,      /* 12, correlated drain & gate noise node 2, when rnoimod = 1 */
  omiBSIMBULKt        /* 13, self-heating node */
} omiBSIMBULKStdNode;
/* end: for BSIMBULK (W. Rhett Davis, 2019/9) */


/* begin: for HiSIM-HV (W. Rhett Davis, 2018/8) */
#define OMI_HiSIMHV_STD_NODE_SIZE_MAX 14 /* maximum HiSIM-HV standard node size */

/* This enumerates all of HiSIM-HV standard nodes */
typedef enum omiHiSIMHVStdNode
{
  omiHiSIMHVd,           /* 0, external drain */
  omiHiSIMHVg,           /* 1, external gate */
  omiHiSIMHVs,           /* 2, external source */
  omiHiSIMHVb,           /* 3, external body */
  omiHiSIMHVsub,         /* 4, substrate */
  omiHiSIMHVtemp,        /* 5, self-heating node */
  omiHiSIMHVdp,          /* 6, internal drain, when corsrd < 0 */
  omiHiSIMHVgp,          /* 7, internal gate */
  omiHiSIMHVsp,          /* 8, internal source, when corsrd < 0 */
  omiHiSIMHVbp,          /* 9, internal body */
  omiHiSIMHVdb,          /* 10, drain-bulk diode connection */
  omiHiSIMHVsb,          /* 11, source-bulk diode connection */
  omiHiSIMHVqi,          /* 12, NQS inversion charge node */
  omiHiSIMHVqb           /* 13, NQS bulk charge node */
} omiHiSIMHVStdNode;
/* end: for HiSIM-HV (W. Rhett Davis, 2018/8) */

/* begin: for PSP (W. Rhett Davis, 2018/8) */
#define OMI_PSP_STD_NODE_SIZE_MAX 22 /* maximum PSP standard node size */

/* This enumerates all of PSP standard nodes */
typedef enum omiPSPStdNode
{
  omiPSPd,         /* 0, external drain */
  omiPSPg,         /* 1, external gate */
  omiPSPs,         /* 2, external source */
  omiPSPb,         /* 3, external bulk */
  omiPSPdt,        /* 4, self-heating node */
  omiPSPnoi,       /* 5, internal noise node */
  omiPSPgp,        /* 6, internal gate */
  omiPSPsi,        /* 7, internal source */
  omiPSPdi,        /* 8, internal drain */
  omiPSPbp,        /* 9, internal bulk connection for channel */
  omiPSPbi,        /* 10, internal bulk connection for well */
  omiPSPbs,        /* 11, internal bulk connection for source junction */
  omiPSPbd,        /* 12, internal bulk connection for drain junction */
  omiPSPint1,      /* 13, Internal node 1 for spline collocation (NQS) */
  omiPSPint2,      /* 14, Internal node 2 for spline collocation (NQS) */
  omiPSPint3,      /* 15, Internal node 3 for spline collocation (NQS) */
  omiPSPint4,      /* 16, Internal node 4 for spline collocation (NQS) */
  omiPSPint5,      /* 17, Internal node 5 for spline collocation (NQS) */
  omiPSPint6,      /* 18, Internal node 6 for spline collocation (NQS) */
  omiPSPint7,      /* 19, Internal node 7 for spline collocation (NQS) */
  omiPSPint8,      /* 20, Internal node 8 for spline collocation (NQS) */
  omiPSPint9       /* 21, Internal node 9 for spline collocation (NQS) */
} omiPSPStdNode;
/* end: for PSP (W. Rhett Davis, 2018/8) */


/* begin: for ASM (W. Rhett Davis, 2019/8) */
#define OMI_ASM_STD_NODE_SIZE_MAX 18 /* maximum ASM standard node size */

/* This enumerates all of ASM standard nodes */
typedef enum omiASMStdNode
{
  omiASMd,           /* 0, extrinsic drain */
  omiASMg,           /* 1, extrinsic gate */
  omiASMs,           /* 2, extrinsic source */
  omiASMb,           /* 3, extrinsic body */
  omiASMdi,          /* 4, intrinsic drain */
  omiASMgi,          /* 5, intrinsic gate */
  omiASMsi,          /* 6, intrinsic source */
  omiASMtrap1,       /* 7, gate trap-voltage node */
  omiASMtrap2,       /* 8, drain trap-voltage node */
  omiASMdt,          /* 9, self-heating node */
  omiASMfp1,         /* 10, intrinsic field-plate drain node 1 */
  omiASMfp2,         /* 11, intrinsic field-plate drain node 2 */
  omiASMfp3,         /* 12, intrinsic field-plate drain node 3 */
  omiASMfp4,         /* 13, intrinsic field-plate drain node 4 */
  omiASMfp1s,        /* 14, intrinsic field-plate source node 1 */
  omiASMfp2s,        /* 15, intrinsic field-plate source node 2 */
  omiASMfp3s,        /* 16, intrinsic field-plate source node 3 */
  omiASMfp4s         /* 17, intrinsic field-plate source node 4 */
} omiASMStdNode;
/* end: for ASM (W. Rhett Davis, 2019/8) */

/* begin: for MVSG (W. Rhett Davis, 2019/8) */
#define OMI_MVSG_STD_NODE_SIZE_MAX 22 /* maximum MVSG standard node size */

/* This enumerates all of MVSG standard nodes */
typedef enum omiMVSGStdNode
{
  omiMVSGd,         /* 0, external drain */
  omiMVSGg,         /* 1, external gate */
  omiMVSGs,         /* 2, external source */
  omiMVSGb,         /* 3, external body */
  omiMVSGdi,        /* 4, internal drain */
  omiMVSGgi,        /* 5, internal gate */
  omiMVSGsi,        /* 6, internal source */
  omiMVSGfps1,      /* 7, internal field-plate source node 1 */
  omiMVSGfps2,      /* 8, internal field-plate source node 2 */
  omiMVSGfps3,      /* 9, internal field-plate source node 3 */
  omiMVSGfps4,      /* 10, internal field-plate source node 4 */
  omiMVSGfp1,       /* 11, internal field-plate drain node 1 */
  omiMVSGfp2,       /* 12, internal field-plate drain node 2 */
  omiMVSGfp3,       /* 13, internal field-plate drain node 3 */
  omiMVSGfp4,       /* 14, internal field-plate drain node 4 */
  omiMVSGdrc,       /* 15, drain contact resistance node */
  omiMVSGsrc,       /* 16, source contact resistance node */
  omiMVSGtr,        /* 17, primary charge trapping node */
  omiMVSGtr1,       /* 18, secondary charge trapping node */
  omiMVSGxt1,       /* 19, gm-dispersion node 1 */
  omiMVSGxt2,       /* 20, gm-dispersion node 2 */
  omiMVSGdt         /* 21, self-heating node */
} omiMVSGStdNode;
/* end: for MVSG (W. Rhett Davis, 2019/8) */

/* begin: for L-UTSOI (W. Rhett Davis, 2020/4) */
#define OMI_LUTSOI_STD_NODE_SIZE_MAX 6 /* maximum L-UTSOI standard node size */

/* This enumerates all of L-UTSOI standard nodes */
typedef enum omiLUTSOIStdNode
{
  omiLUTSOId,         /* 0, drain */
  omiLUTSOIg,         /* 1, gate */
  omiLUTSOIs,         /* 2, source */
  omiLUTSOIb,         /* 3, body */
  omiLUTSOInsig,      /* 4, internal node for noise model */
  omiLUTSOIdt         /* 5, self-heating node */
} omiLUTSOIStdNode;
/* end: for L-UTSOI (W. Rhett Davis, 2020/4) */


/* This is used to indicate what type of physical value is represented by a node */
typedef enum omiNodeType
{
  omiNodeTypePotential, /* such things as voltage, position, temperature */
  omiNodeTypeFlow       /* such things as current, velocity, power flow */
}
omiNodeType;


/* This is used by the simulator when initializing the omiEvalData structure
 * in order to instruct the models as to how much evaluation/calculation
 * is needed during subsequent calls to the evaluation functions.
 */
typedef enum omiEvalLevel
{
  omiEvalNothing,       /* nothing */
  omiEvalRhs,           /* for future use only.  Not defined for OMI */ 
  omiEvalDeriv,         /* for future use only.  Not defined for OMI */ 
  omiEvalAll,           /* all */
  omiEvalTopo           /* topology */
}
omiEvalLevel;

/* This enumerates all of stamp type */
typedef enum omiStampType
{
  omiStampAll/* placeholder */
  /* may add more types */
}
omiStampType;


/* This structure defines variable type for probe */
typedef struct omiProbeData
{
  char   *name;         /* name */
  double value;         /* value */
} omiProbeData;

/* This structure defines variable type for nosie */
typedef struct omiNoiseData
{
  char   *name;         /* name */
  double value;         /* value */
  int    term1;         /* terminal1 */
  int    term2;         /* terminal2 */
} omiNoiseData;

/* This structure is used to control evaluation of the model */
typedef struct omiEvalData
{
  omiEvalLevel evalI;        /* I/G evaluation for omiEvaluate( ) */
  omiEvalLevel evalQ;        /* Q/C evaluation for omiEvaluate( ) */
  omiStampType type;         /* stamp type, reserved */
  double       time;         /* time during transient analysis for aging models */
  double       step;         /* time step during transient analysis for aging models */
  double       freq;         /* frequency during AC or noise analysis */
  double       gmin;         /* gmin */
  unsigned     limiting:1;   /* limiting flag, reserved; it should not be used in OMI releases */
  double       *workData;    /* V/I/G/Q/C information that may be changed each time omiEvaluate is called */
  void         *specData;    /* instance specific data that could be reused by all steps */
  void         *coreData;    /* core model data */
  omiProbeData *probeData;   /* probe data */
  omiNoiseData *noiseData;   /* noise data */
} omiEvalData;

/* OMI virtual function table */
typedef struct omiIft
{
  /* memory size  for simulator to allocate memory for omiEvalData->workData structure. 
     omiEvalData->workData is designed to pass general data such as V/I/G/Q/C 
     between OMI model and simulator each evaluation.  */
  int    workDataSize; 
  
  /* memory size of omiEvalData->specData for instance specific data */
  int    specDataSize;
  
  /* number of probe variable (omiEvalData->probeData) */
  int    probeDataSize;
  
  /* number of noise variable (omiEvalData->noiseData) */
  int    noiseDataSize;
  
  /* model evaluation function */
  int    (*omiEvaluate) (void *pModelData, void *pInstData, omiEvalData *pEvalData);
  
  /* noise evaluation function */
  int    (*omiNoise) (void *pModelData, void *pInstData, omiEvalData *pEvalData);
  
  /* This function performs node mapping operation when new internal node is added into standard core device topology. */
  int    (*omiSetTopology) (omiEvalData *pEvalData, int *stdNode, int *newNode);
  
  /* This function returns number of new node introduced by OMI2 device */
  int    (*omiTermCount) (omiEvalData *pEvalData);
  
  /* This function returns node physical value type. */
  omiNodeType (*omiTerminalType)(omiEvalData *pEvalData, int term_index);
  
  /* This function returns number of constant conductance */
  int    (*omiConstCondCount) (omiEvalData *pEvalData);
  
  /* This function returns matrix row location of each constant conductance given by dindex */
  int    (*omiConstCondRow) (omiEvalData *pEvalData, int dindex, int in_out); 
  
  /* This function returns matrix column location of each constant conductance given by dindex */
  int    (*omiConstCondColumn) (omiEvalData *pEvalData, int dindex, int plus_minus);
   
  /* This function returns the value of each constant conductance given by dindex */
  double (*omiConstCondValue) (omiEvalData *pEvalData, int dindex);
  
  /* This function returns number of branch currents */
  int    (*omiISize) (omiEvalData *pEvalData);
  
  /* This function returns matrix row location of each branch current given by rhs_index */
  int    (*omiITermRow) (omiEvalData *pEvalData, int rhs_index, int in_out);
  
  /* This function returns offset of current, given by rhs_index, in omiWorkData structure */
  int    (*omiIWorkDataOffset) (omiEvalData *pEvalData, int rhs_index);
  
  /* This function returns # of derivatives for each branch current given by rhs_index */
  int    (*omiIderivSize) (omiEvalData *pEvalData, int rhs_index);
  
  /* This function returns offset of branch current's derivatives in omiWorkData structure */
  int    (*omiIderivWorkDataOffset) (omiEvalData *pEvalData, int rhs_index, int deriv_index);
  
  /* This function returns matrix column location of "rhs_index" current's "derive_index" derivative */
  int    (*omiIderivTermCol) (omiEvalData *pEvalData, int rhs_index, int deriv_index, int plus_minus);
  
  /* This function returns number of all charges introduced by OMI2 */
  int    (*omiQSize) (omiEvalData *pEvalData);
  
  /* This function returns matrix row location of each charge given by rhs_index */
  int    (*omiQTermRow) (omiEvalData *pEvalData, int rhs_index, int in_out);
  
  /* This function returns offset of charge, given by rhs_index, in omiWorkdata structure */
  int    (*omiQWorkDataOffset) (omiEvalData *pEvalData, int rhs_index);
  
  /* This function returns # of derivatives for each charge */
  int    (*omiQderivSize) (omiEvalData *pEvalData, int rhs_index);
  
  /* This function returns offset of charge derivatives in omiWorkData structure */
  int    (*omiQderivWorkDataOffset) (omiEvalData *pEvalData, int rhs_index, int deriv_index);
  
  /* This function returns matrix column location of each charge derivative given by "rhs_index" and "derive_index" */
  int    (*omiQderivTermCol) (omiEvalData *pEvalData, int rhs_index, int deriv_index, int plus_minus);
  
  /* This function integrates dAge (initialize dAge when time = 0) */
  int    (*omiIntegrate)(void *pModelData, void *pInstData, omiEvalData *pEvalData);
} omiIft;


typedef struct omiModuleIft
{

   /* Model Name ID for the type of module (e.g. 5000 for Verilog-A),
      assigned by OMI code to match value passed to
      omiInitializeModule. */
   int modelID;

   /* Module ID number, assigned by OMI code to match value passed to
      omiInitializeModule by the simulator. */
   int moduleID;

   /* Module name string, statically allocated and assigned by OMI
      code to match value passed to omiInitializeModule by the
      simulator. */
   char *moduleName;

   /* Number of parameters in the modParamName, modParamDirection,
      modParamIndexIn, and modParamIndexOut arrays */
   int numModParam;

   /* Array of strings statically allocated and assigned by OMI code,
      indicating Verilog-A parameters to be included in the param and
      value fields of the omiModel struct passed to omiUpdate.  Each
      string should match the parameter name as it appears in the
      source code. */
   String * modParamName;

   /* Array of integers statically allocated and assigned by OMI code,
      indicating the direction of each Verilog-A Parameter listed in
      the modParamName array.
         0 – input (appears in param and value fields of omiModel
             struct passed to omiUpdate)
         1 – output (appears in param_o and value_o fields of omiModel
             struct passed to omiUpdate)
         2 – input and output (appears in both locations)  */
   int *modParamDirection;

   /* Array of integers statically allocated by OMI code.  For each
      Verilog-A parameter listed in the modParamName array, gives the
      index into the param and value fields of the omiModel struct, or
      a negative number on error.  This array will be assigned by the
      simulator before the first call to omiUpdate. */
   int *modParamIndexIn;

   /* Array of integers statically allocated by OMI code.  For each
      Verilog-A parameter listed in the modParamName array, gives the
      index into the param_o and value_o fields of the omiModel
      struct, or a negative number on error.  This array will be
      assigned by the simulator before the first call to omiUpdate. */
   int *modParamIndexOut;

   /* Number of parameters in the instParamName, instParamDirection,
      instParamIndexIn, and instParamIndexOut arrays */
   int numInstParam;

   /* Array of strings statically allocated and assigned by OMI code,
      indicating Verilog-A parameters to be included in the param and
      value fields of the omiInstance struct passed to omiUpdate.  It
      is expected that these parameters will have a type attribute
      annotated in the Verilog-A code, and that type attribute will be
      set to “instance”.  */
   String * instParamName;

   /* Array of integers statically allocated and assigned by OMI code,
      indicating the direction of each Verilog-A Parameter listed in the
      instParamName array.
         0 – input (appears in param and value fields of omiInstance
             struct passed to omiUpdate)
         1 – output (appears in param_o and value_o fields of
             omiInstance struct passed to omiUpdate)
         2 – input and output (appears in both locations)  */
   int *instParamDirection;

   /* Array of integers statically allocated by OMI code.  For each
      Verilog-A parameter listed in the instParamName array, gives the
      index into the param and value fields of the omiInstance struct,
      or a negative number on error.  This array will be assigned by
      the simulator before the first call to omiUpdate. */
   int *instParamIndexIn;

   /* Array of integers statically allocated by OMI code.  For each
      Verilog-A parameter listed in the instParamName array, gives the
      index into the param_o and value_o fields of the omiInstance
      struct, or a negative number on error.  This array will be
      assigned by the simulator before the first call to omiUpdate. */
   int *instParamIndexOut;

   /* Number of variables in the coreDataVarName and coreDataVarIndex
      arrays */
   int numCoreDataVar;

   /* Array of strings statically allocated and assigned by OMI code,
      indicating Verilog-A variables to be included in the coreData
      field of the omiEvalData struct passed to the omiIntegrate
      function (as specified in the omiIft struct returned by
      omiCreate).  Each string should match the parameter name as it
      appears in the source code. */
   String *coreDataVarName;

   /* Array of integers statically allocated by OMI code.  For each
      Verilog-A parameter listed in the coreDataVarName array, gives
      the index into the coreData field of the omiEvalData struct, or
      a negative number on error.  This array will be assigned by the
      simulator before the first call to the omiIntegrate function (as
      specified in the omiIft struct returned by omiCreate).  */
   int *coreDataVarIndex;

} omiModuleIft;



/* declare function */
extern char *omiCreate (int spiceType, int id, int level, void *pModelData);
extern int omiPrintAge (omiCKT *pCKT);
extern int omiFreeAge ();
extern int omiUdf (double *output, const String strArg, const int numArgs, const double *args);
extern int omiFreeUdf ();


#endif /* OMIIFT_H */


/* end of $RCSfile: omiIft.h,v $ */
