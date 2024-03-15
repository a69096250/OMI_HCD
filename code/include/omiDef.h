/*
 ****************************************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 ****************************************************************************
 *  File        : omiDef.h 
 *  Date        : 2016-11-22
 *  Description : OMI interface structures
 */


#ifndef OMIDEF_H
#define OMIDEF_H


/* OMI MOS device type */
#ifndef NMOS
#define NMOS 1
#define PMOS -1
#endif /* NMOS */

/* OMI function return status */
#define OMI_BADPARAM -1
#define OMI_OK       0
#define OMI_ERROR    1
#define OMI_WARNING  2
#define OMI_AGE      3

/* define model types */
#define OMI_MOS_MODEL   24

/* define model name id (may add more models) */
#define OMI_MOS_BSIM3     2400
#define OMI_MOS_BSIM4     2401
#define OMI_MOS_PSP       2402
#define OMI_MOS_HiSIMHV   2403
#define OMI_MOS_BSIMCMG   2404
#define OMI_MOS_HiSIM2    2405
#define OMI_MOS_BSIMSOI   2406
#define OMI_MOS_BSIMIMG   2407
#define OMI_MOS_BSIMBULK  2408
#define OMI_MOS_HiSIMSOTB 2409
#define OMI_MOS_HiSIMSOI  2410
#define OMI_MOS_ASM       2411
#define OMI_MOS_MVSG      2412
#define OMI_MOS_LUTSOI    2413
#define OMI_VLOGA         5000


/* define NULL */
#ifndef NULL
#define NULL 0
#endif /* NULL */

/* define eval types */
#define evalTypeWL    0	/* evaluate W & L equations and then update */
#define evalTypeOther 1	/* evaluate other equations and then update */
#define evalTypeStart 2 /* pre-process before evaluation, reserved */
#define evalTypeEnd   3 /* post-process after evaluation, reserved */

/* define default value */
#define OMI_AUNDEF -1.23456789e-29

#ifdef _WIN32
#define strncasecmp strnicmp
#endif /* _WIN32 */


/* define data types */
typedef char *String;
typedef int ParamId;


/* OMI interface struct */
typedef struct omiSelectModelBin
{
  double dlmin;           /* lmin variation */
  double dlmax;           /* lmax variation */
  double dwmin;           /* wmin variation */
  double dwmax;           /* wmax variation */
} omiSelectModelBin;

typedef struct omiCKT
{
  double CKTtemp;         /* input  - simulation temperature */
  double CKTnomTemp;      /* input  - nominal temperature */
  double scale;           /* input  - scaling factor for geometric instance parameters;
                                      if the simulator supports more than one scaling factor,
                                      this value should be the final product of all valid factors. */
  double scalm;           /* input  - scaling factor for geometric model parameters;
                                      if the simulator supports more than one scaling factor,
                                      this value should be the final product of all valid factors.
                                      If no scaling is to be performed (or the simulator does not
                                      support such scaling), this parameter should be set to 1. */
  int    evalType;        /* input  - 0: evalTypeWL
                                      1: evalTypeOther */
  int    spiceType;       /* input  - spice type, reserved; simulators shall assign it to -1 as default.
                                      Or this field may be used with omiModel->level to identify
                                      proprietary models in a specific simulator.*/
  int    (*print) (const char *fmt, ...);    /* input  - pointer to simulator's print function to help debugging OMI model code. */
  int    omiAge;          /* input  - option omiAge to turn on/off aging flow */
  int    tblSize;         /* input  - number of instances that use OMI model, used by omiHashCreate in
                                      code/src/ut/omiHash.c to optimize performance of segmented hash for Age struct lookup.
                                      If simulator sets to 0, OMI will use the default 128*2048. This will not affect results.
                                      Simulator must not set to a negative number. */
  char   *omiInput;       /* input  - input file name including full path to read back OMI information:
                                      If option omiInput is specified (e.g. $file_name),
                                      in the first run, simulators will set it to a full file name with the same full path as the 
                                      model file or netlist file (e.g. $file_model_or_netlist_path).  
                                      Thus the final full name looks like  ($file_model_or_netlist_path/$file_name).
                                      If option omiInput is not specified,
                                      simulators will set it to NULL in the first run;
                                      For the case of omiAge=1, whether option omiInput specified or not,
                                      simulators will set it to *.omi# (with full path specified by simulator) generated by
                                      output of last run for latter runs; 
                                      For the case of omiage=0, omiInput of latter runs will still be the same as the first run */

  char   *omiOutput;      /* input  - output full file name (follows simulator output file name convention)
                                      with postfix ".omi#" including full path.
                                      OMI will save information to omiOutput(usually for save/restore) */
  int    omiSave;         /* input  - option omiSave to enable/disable aging information saved to *.omiage# */
  char   *degFile;        /* input  - output file name (follows simulator output file name convention)
                                      with postfix ".omideg#" including full path.
                                      OMI save aging information to degFile with text format (for customer's view)
                                      according to sorting */
  char   *omiSort;        /* input  -  option omiSort, reserved; could be used to sort aging information */
} omiCKT;

typedef struct omiModel
{
  int    id;              /* input  - OMI_MOS_BSIM4 for BSIM4 models */
  int    modelType;       /* input  - +1: NMOS
                                      -1: PMOS */
  int    level;           /* input  - model level, reserved; simulators shall assign it to -1 as default.
                                      Or this field may be used with omiCKT->spiceType to identify
                                      proprietary models in a specific simulator. */
  int    printModel;      /* input  - print model parameter flag */
  String modelName;       /* input  - model name */
  int    modelSize;       /* input  - number of model parameters, assigned by simulators */
  String *param;          /* input  - model parameter name array allocated and assigned by simulators */
  double *value;          /* input  - model parameter value array allocated and assigned by simulators */
  int    modelSize_o;     /* output - number of model parameters, assigned by OMI libraries */
  String *param_o;        /* output - model parameter name array allocated and assigned by OMI libraries */
  double *value_o;        /* output - model parameter value array allocated and assigned by OMI libraries*/
  void   *pModelData;     /*          pointer of OMI model data structure,
						                       e.g. &BSIM4Model in code/src/models/bsim4/omiBSIM4.c
                             output - if modelSize > 0, OMI library allocates, assigns, 
                                      and returns pointer to simulator
                             input  - if modelSize = 0, simulator allocates, copies from
                                      previous pointer, and passes new pointer to OMI */
  int    modelDataSize;	  /* output - size of OMI model data structure */
  omiSelectModelBin *bin; /* output - slot to return bin variation */
} omiModel;

typedef struct omiInstance
{
  int    printWarn;       /* input  - print warning message flag */
  String instName;        /* input  - instance name */
  int    instSize;        /* input  - number of instance parameters, assigned by simulators */
  String *param;          /* input  - instance parameter name array allocated and assigned by simulators */
  double *value;          /* input  - instance parameter value array allocated and assigned by simulators */
  int    instSize_o;      /* output - number of instance parameters, assigned by OMI libraries */
  String *param_o;        /* output - instance parameter name array allocated and assigned by OMI libraries */
  double *value_o;        /* output - instance parameter value array allocated and assigned by OMI libraries */
  void   *pInstData;      /*          pointer of OMI instance data structure,
						                       e.g. &BSIM4Inst in code/src/models/bsim4/omiBSIM4.c
                             output - if instSize > 0, OMI library allocates, assigns, 
                                      and returns pointer to simulator
                             input  - if instSize = 0, simulator allocates, copies from 
                                      previous pointer, and passes new pointer to OMI */
  int    instDataSize;    /* output - size of OMI instance data structure */
} omiInstance;


/* declare function */
extern int (*omiPrint) (const char *fmt, ...);
extern int omiUpdate (omiCKT *pCKT, omiModel *pModel, omiInstance *pInstance);

#endif /* OMIDEF_H */

/* end of $RCSfile: omiDef.h,v $ */
