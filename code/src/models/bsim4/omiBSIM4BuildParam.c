/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4BuildParam.c
 *  Date        : 2010_1123
 *  Description : To build instance/model parameter
 */


#include "omiBSIM4Def.h"


/* instance parameter (output) name array */
static char   b4_inst_param_o[B4_INST_SIZE_o][PARAM_LEN] =
{
  "l",
  "w",
  "m",
  "nf",
  "ad",
  "as",
  "pd",
  "ps",
  "nrd",
  "nrs",
  "sa",
  "sb",
  "sd",
  "sca",
  "scb",
  "scc",
  "delvto",
  "mulu0",
};

/* instance parameter (output) value array */
static double b4_inst_value_o[B4_INST_SIZE_o];

/* model parameter (output) name array */
static char   b4_mod_param_o[B4_MOD_SIZE_o][PARAM_LEN] =
{
  "toxe",
  "xl",
  "xw",
  "vth0",
  "lvth0",
  "wvth0",
  "pvth0",
  "k2",
  "u0",
  "lu0",
  "wu0",
  "pu0",
  "eta0",
  "vsat",
  "lvsat",
  "wvsat",
  "pvsat",
  "dmci",
  "dmcg",
  "tnom",

};

/* model parameter (output) value array */
static double b4_mod_value_o[B4_MOD_SIZE_o];

static omiSelectModelBin b4_mod_bin;

String  omi_b4_inst_param_o[B4_INST_SIZE_o];
double *omi_b4_inst_value_o = b4_inst_value_o;
String  omi_b4_mod_param_o[B4_MOD_SIZE_o];
double *omi_b4_mod_value_o = b4_mod_value_o;
omiSelectModelBin *omi_b4_mod_bin = &b4_mod_bin;

parNode *omiBSIM4InstHeader = NULL;
parNode *omiBSIM4ModelHeader = NULL;

void omiBSIM4BuildInstParam ()
{
  int i = 0;

  if (omiBSIM4InstHeader != NULL)
    return;

  omiInsertNode(&omiBSIM4InstHeader, "l", B4_INST_l);
  omiInsertNode(&omiBSIM4InstHeader, "w", B4_INST_w);
  omiInsertNode(&omiBSIM4InstHeader, "m", B4_INST_m);
  omiInsertNode(&omiBSIM4InstHeader, "nf", B4_INST_nf);
  omiInsertNode(&omiBSIM4InstHeader, "ad", B4_INST_ad);
  omiInsertNode(&omiBSIM4InstHeader, "as", B4_INST_as);
  omiInsertNode(&omiBSIM4InstHeader, "pd", B4_INST_pd);
  omiInsertNode(&omiBSIM4InstHeader, "ps", B4_INST_ps);
  omiInsertNode(&omiBSIM4InstHeader, "nrd", B4_INST_nrd);
  omiInsertNode(&omiBSIM4InstHeader, "nrs", B4_INST_nrs);
  omiInsertNode(&omiBSIM4InstHeader, "sa", B4_INST_sa);
  omiInsertNode(&omiBSIM4InstHeader, "sb", B4_INST_sb);
  omiInsertNode(&omiBSIM4InstHeader, "sd", B4_INST_sd);
  omiInsertNode(&omiBSIM4InstHeader, "sca", B4_INST_sca);
  omiInsertNode(&omiBSIM4InstHeader, "scb", B4_INST_scb);
  omiInsertNode(&omiBSIM4InstHeader, "scc", B4_INST_scc);
  omiInsertNode(&omiBSIM4InstHeader, "delvto", B4_INST_delvto);
  omiInsertNode(&omiBSIM4InstHeader, "mulu0", B4_INST_mulu0);

  omiInsertNode(&omiBSIM4InstHeader, "multi",           B4_INST_multi);
  omiInsertNode(&omiBSIM4InstHeader, "scale",           B4_INST_scale);
  omiInsertNode(&omiBSIM4InstHeader, "_dmcg",           B4_INST__dmcg);
  omiInsertNode(&omiBSIM4InstHeader, "_dmci",           B4_INST__dmci);
  omiInsertNode(&omiBSIM4InstHeader, "_xw",             B4_INST__xw);
  omiInsertNode(&omiBSIM4InstHeader, "_xl",             B4_INST__xl);
  omiInsertNode(&omiBSIM4InstHeader, "_delvto",         B4_INST__delvto);
  omiInsertNode(&omiBSIM4InstHeader, "_mulu0",          B4_INST__mulu0);
  omiInsertNode(&omiBSIM4InstHeader, "prnflag",         B4_INST_prnflag);


  for (i = 0; i < B4_INST_SIZE_o; i++)
    omi_b4_inst_param_o[i] = b4_inst_param_o[i];

  return;
}


void omiBSIM4BuildModelParam ()
{
  int i = 0;

  if (omiBSIM4ModelHeader != NULL)
    return;

  omiInsertNode(&omiBSIM4ModelHeader, "tox_c",               B4_MOD_tox_c);
  omiInsertNode(&omiBSIM4ModelHeader, "tox_g",               B4_MOD_tox_g);
  omiInsertNode(&omiBSIM4ModelHeader, "tox_max",             B4_MOD_tox_max);
  omiInsertNode(&omiBSIM4ModelHeader, "tox_min",             B4_MOD_tox_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dxl_c",               B4_MOD_dxl_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dxl_g",               B4_MOD_dxl_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dxl_max",             B4_MOD_dxl_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dxl_min",             B4_MOD_dxl_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dxw_c",               B4_MOD_dxw_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dxw_g",               B4_MOD_dxw_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dxw_max",             B4_MOD_dxw_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dxw_min",             B4_MOD_dxw_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dvth_c",              B4_MOD_dvth_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dvth_g",              B4_MOD_dvth_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dvth_max",            B4_MOD_dvth_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dvth_min",            B4_MOD_dvth_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvth_c",             B4_MOD_dlvth_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvth_g",             B4_MOD_dlvth_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvth_max",           B4_MOD_dlvth_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvth_min",           B4_MOD_dlvth_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvth_c",             B4_MOD_dwvth_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvth_g",             B4_MOD_dwvth_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvth_max",           B4_MOD_dwvth_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvth_min",           B4_MOD_dwvth_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvth_c",             B4_MOD_dpvth_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvth_g",             B4_MOD_dpvth_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvth_max",           B4_MOD_dpvth_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvth_min",           B4_MOD_dpvth_min);
  omiInsertNode(&omiBSIM4ModelHeader, "du0_c",               B4_MOD_du0_c);
  omiInsertNode(&omiBSIM4ModelHeader, "du0_g",               B4_MOD_du0_g);
  omiInsertNode(&omiBSIM4ModelHeader, "du0_max",             B4_MOD_du0_max);
  omiInsertNode(&omiBSIM4ModelHeader, "du0_min",             B4_MOD_du0_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dlu0_c",              B4_MOD_dlu0_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dlu0_g",              B4_MOD_dlu0_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dlu0_max",            B4_MOD_dlu0_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dlu0_min",            B4_MOD_dlu0_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dwu0_c",              B4_MOD_dwu0_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dwu0_g",              B4_MOD_dwu0_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dwu0_max",            B4_MOD_dwu0_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dwu0_min",            B4_MOD_dwu0_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dpu0_c",              B4_MOD_dpu0_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dpu0_g",              B4_MOD_dpu0_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dpu0_max",            B4_MOD_dpu0_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dpu0_min",            B4_MOD_dpu0_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dvsat_c",             B4_MOD_dvsat_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dvsat_g",             B4_MOD_dvsat_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dvsat_max",           B4_MOD_dvsat_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dvsat_min",           B4_MOD_dvsat_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvsat_c",            B4_MOD_dlvsat_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvsat_g",            B4_MOD_dlvsat_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvsat_max",          B4_MOD_dlvsat_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dlvsat_min",          B4_MOD_dlvsat_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvsat_c",            B4_MOD_dwvsat_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvsat_g",            B4_MOD_dwvsat_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvsat_max",          B4_MOD_dwvsat_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dwvsat_min",          B4_MOD_dwvsat_min);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvsat_c",            B4_MOD_dpvsat_c);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvsat_g",            B4_MOD_dpvsat_g);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvsat_max",          B4_MOD_dpvsat_max);
  omiInsertNode(&omiBSIM4ModelHeader, "dpvsat_min",          B4_MOD_dpvsat_min);



/***************************/
  omiInsertNode(&omiBSIM4ModelHeader, "delvto",          B4_MOD_delvto);
  omiInsertNode(&omiBSIM4ModelHeader, "mulu0",           B4_MOD_mulu0);
  omiInsertNode(&omiBSIM4ModelHeader, "mis_a_1",         B4_MOD_mis_a_1);
  omiInsertNode(&omiBSIM4ModelHeader, "mis_a_2",         B4_MOD_mis_a_2);
  omiInsertNode(&omiBSIM4ModelHeader, "parl1",           B4_MOD_parl1);
  omiInsertNode(&omiBSIM4ModelHeader, "parl2",           B4_MOD_parl2);
  omiInsertNode(&omiBSIM4ModelHeader, "saref0",          B4_MOD_saref0);
  omiInsertNode(&omiBSIM4ModelHeader, "sbref0",          B4_MOD_sbref0);
  omiInsertNode(&omiBSIM4ModelHeader, "wlod0",           B4_MOD_wlod0);
  omiInsertNode(&omiBSIM4ModelHeader, "ku00",            B4_MOD_ku00);
  omiInsertNode(&omiBSIM4ModelHeader, "lku00",           B4_MOD_lku00);
  omiInsertNode(&omiBSIM4ModelHeader, "wku00",           B4_MOD_wku00);
  omiInsertNode(&omiBSIM4ModelHeader, "pku00",           B4_MOD_pku00);
  omiInsertNode(&omiBSIM4ModelHeader, "tku00",           B4_MOD_tku00);
  omiInsertNode(&omiBSIM4ModelHeader, "llodku00",        B4_MOD_llodku00);
  omiInsertNode(&omiBSIM4ModelHeader, "wlodku00",        B4_MOD_wlodku00);
  omiInsertNode(&omiBSIM4ModelHeader, "kvsat0",          B4_MOD_kvsat0);
  omiInsertNode(&omiBSIM4ModelHeader, "kvth00",          B4_MOD_kvth00);
  omiInsertNode(&omiBSIM4ModelHeader, "lkvth00",         B4_MOD_lkvth00);
  omiInsertNode(&omiBSIM4ModelHeader, "wkvth00",         B4_MOD_wkvth00);
  omiInsertNode(&omiBSIM4ModelHeader, "pkvth00",         B4_MOD_pkvth00);
  omiInsertNode(&omiBSIM4ModelHeader, "llodvth0",        B4_MOD_llodvth0);
  omiInsertNode(&omiBSIM4ModelHeader, "wlodvth0",        B4_MOD_wlodvth0);
  omiInsertNode(&omiBSIM4ModelHeader, "stk20",           B4_MOD_stk20);
  omiInsertNode(&omiBSIM4ModelHeader, "lodk20",          B4_MOD_lodk20);
  omiInsertNode(&omiBSIM4ModelHeader, "steta00",         B4_MOD_steta00);
  omiInsertNode(&omiBSIM4ModelHeader, "lodeta00",        B4_MOD_lodeta00);
  omiInsertNode(&omiBSIM4ModelHeader, "rn0xb",           B4_MOD_rn0xb);
  omiInsertNode(&omiBSIM4ModelHeader, "_tcj",            B4_MOD__tcj);
  omiInsertNode(&omiBSIM4ModelHeader, "_tcjsw",          B4_MOD__tcjsw);
  omiInsertNode(&omiBSIM4ModelHeader, "_tcjswg",         B4_MOD__tcjswg);
  omiInsertNode(&omiBSIM4ModelHeader, "_tpb",            B4_MOD__tpb);
  omiInsertNode(&omiBSIM4ModelHeader, "_tpbsw",          B4_MOD__tpbsw);
  omiInsertNode(&omiBSIM4ModelHeader, "_tpbswg",         B4_MOD__tpbswg);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtis",           B4_MOD__xtis);
  omiInsertNode(&omiBSIM4ModelHeader, "_njs",            B4_MOD__njs);
  omiInsertNode(&omiBSIM4ModelHeader, "_bvs",            B4_MOD__bvs);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjs",            B4_MOD__mjs);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjsws",          B4_MOD__mjsws);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjswgs",         B4_MOD__mjswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_jss",            B4_MOD__jss);
  omiInsertNode(&omiBSIM4ModelHeader, "_jsws",           B4_MOD__jsws);
  omiInsertNode(&omiBSIM4ModelHeader, "_jswgs",          B4_MOD__jswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtss",           B4_MOD__jtss);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtssws",         B4_MOD__jtssws);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtsswgs",        B4_MOD__jtsswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_njts",           B4_MOD__njts);
  omiInsertNode(&omiBSIM4ModelHeader, "_njtssw",         B4_MOD__njtssw);
  omiInsertNode(&omiBSIM4ModelHeader, "_njtsswg",        B4_MOD__njtsswg);
  omiInsertNode(&omiBSIM4ModelHeader, "_njtsdx",         B4_MOD__njtsdx);
  omiInsertNode(&omiBSIM4ModelHeader, "_njtsswdx",       B4_MOD__njtsswdx);
  omiInsertNode(&omiBSIM4ModelHeader, "_njtsswgdx",      B4_MOD__njtsswgdx);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjts",          B4_MOD__tnjts);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjtssw",        B4_MOD__tnjtssw);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjtsswg",       B4_MOD__tnjtsswg);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtss",           B4_MOD__vtss);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtssws",         B4_MOD__vtssws);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtsswgs",        B4_MOD__vtsswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtss",           B4_MOD__xtss);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtssws",         B4_MOD__xtssws);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtsswgs",        B4_MOD__xtsswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbs",            B4_MOD__pbs);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbsws",          B4_MOD__pbsws);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbswgs",         B4_MOD__pbswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjs",            B4_MOD__cjs);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjsws",          B4_MOD__cjsws);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjswgs",         B4_MOD__cjswgs);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtid",           B4_MOD__xtid);
  omiInsertNode(&omiBSIM4ModelHeader, "_njd",            B4_MOD__njd);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjd",            B4_MOD__mjd);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjswd",          B4_MOD__mjswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_mjswgd",         B4_MOD__mjswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jsd",            B4_MOD__jsd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jswd",           B4_MOD__jswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jswgd",          B4_MOD__jswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtsd",           B4_MOD__jtsd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtsswd",         B4_MOD__jtsswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_jtsswgd",        B4_MOD__jtsswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjtsd",         B4_MOD__tnjtsd);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjtsswd",       B4_MOD__tnjtsswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_tnjtsswgd",      B4_MOD__tnjtsswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtsd",           B4_MOD__vtsd);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtsswd",         B4_MOD__vtsswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_vtsswgd",        B4_MOD__vtsswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtsd",           B4_MOD__xtsd);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtsswd",         B4_MOD__xtsswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_xtsswgd",        B4_MOD__xtsswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbd",            B4_MOD__pbd);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbswd",          B4_MOD__pbswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_pbswgd",         B4_MOD__pbswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjd",            B4_MOD__cjd);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjswd",          B4_MOD__cjswd);
  omiInsertNode(&omiBSIM4ModelHeader, "_cjswgd",         B4_MOD__cjswgd);
  omiInsertNode(&omiBSIM4ModelHeader, "_dwj",            B4_MOD__dwj);
  omiInsertNode(&omiBSIM4ModelHeader, "_wlc",            B4_MOD__wlc);
  omiInsertNode(&omiBSIM4ModelHeader, "_wln",            B4_MOD__wln);
  omiInsertNode(&omiBSIM4ModelHeader, "_wwc",            B4_MOD__wwc);
  omiInsertNode(&omiBSIM4ModelHeader, "_wwn",            B4_MOD__wwn);
  omiInsertNode(&omiBSIM4ModelHeader, "_wwlc",           B4_MOD__wwlc);
  omiInsertNode(&omiBSIM4ModelHeader, "omimod",          B4_MOD_omimod);
  omiInsertNode(&omiBSIM4ModelHeader, "agemod",          B4_MOD_agemod);
  omiInsertNode(&omiBSIM4ModelHeader, "fvth0_age",       B4_MOD_fvth0_age);
  omiInsertNode(&omiBSIM4ModelHeader, "dagetime",        B4_MOD_dagetime);
  omiInsertNode(&omiBSIM4ModelHeader, "n_age",           B4_MOD_n_age);
  omiInsertNode(&omiBSIM4ModelHeader, "Hs_age",          B4_MOD_Hs_age);
  omiInsertNode(&omiBSIM4ModelHeader, "ms_age",          B4_MOD_ms_age);
  omiInsertNode(&omiBSIM4ModelHeader, "Hg_age",          B4_MOD_Hg_age);
  omiInsertNode(&omiBSIM4ModelHeader, "mg_age",          B4_MOD_mg_age);
  omiInsertNode(&omiBSIM4ModelHeader, "Vgsdmax",         B4_MOD_Vgsdmax);


/***************************/
  omiInsertNode(&omiBSIM4ModelHeader, "toxe",            B4_MOD_toxe);
  omiInsertNode(&omiBSIM4ModelHeader, "xl",              B4_MOD_xl);
  omiInsertNode(&omiBSIM4ModelHeader, "xw",              B4_MOD_xw);
  omiInsertNode(&omiBSIM4ModelHeader, "vth0",            B4_MOD_vth0);
  omiInsertNode(&omiBSIM4ModelHeader, "lvth0",           B4_MOD_lvth0);
  omiInsertNode(&omiBSIM4ModelHeader, "wvth0",           B4_MOD_wvth0);
  omiInsertNode(&omiBSIM4ModelHeader, "pvth0",           B4_MOD_pvth0);
  omiInsertNode(&omiBSIM4ModelHeader, "k2",              B4_MOD_k2);
  omiInsertNode(&omiBSIM4ModelHeader, "u0",              B4_MOD_u0);
  omiInsertNode(&omiBSIM4ModelHeader, "lu0",             B4_MOD_lu0);
  omiInsertNode(&omiBSIM4ModelHeader, "wu0",             B4_MOD_wu0);
  omiInsertNode(&omiBSIM4ModelHeader, "pu0",             B4_MOD_pu0);
  omiInsertNode(&omiBSIM4ModelHeader, "eta0",            B4_MOD_eta0);
  omiInsertNode(&omiBSIM4ModelHeader, "vsat",            B4_MOD_vsat);
  omiInsertNode(&omiBSIM4ModelHeader, "lvsat",           B4_MOD_lvsat);
  omiInsertNode(&omiBSIM4ModelHeader, "wvsat",           B4_MOD_wvsat);
  omiInsertNode(&omiBSIM4ModelHeader, "pvsat",           B4_MOD_pvsat);
  omiInsertNode(&omiBSIM4ModelHeader, "dmci",            B4_MOD_dmci);
  omiInsertNode(&omiBSIM4ModelHeader, "dmcg",            B4_MOD_dmcg);
  omiInsertNode(&omiBSIM4ModelHeader, "tnom",            B4_MOD_tnom);

  for (i = 0; i < B4_MOD_SIZE_o; i++)
    omi_b4_mod_param_o[i] = b4_mod_param_o[i];

  return;
}

static char b4_core_data_param[B4_CORE_DATA_SIZE][PARAM_LEN] =
{
  "vth",
  "vdsat",
  "ids",
  "gds",
  "gm",
  "gmbs",
  "beta",
  "gamma",
  "ibs",
  "ibd",
  "isub",
  "igso",
  "igdo",
  "igb",
  "igcs",
  "igcd",
  "igidl",
  "igisl",
};

String omi_b4_core_data_param[B4_CORE_DATA_SIZE];

void omiBSIM4BuildCoreDataParam ()
{
  int i = 0;

  for (i = 0; i < B4_CORE_DATA_SIZE; i++)
    omi_b4_core_data_param[i] = b4_core_data_param[i];

  return;
}


/* end of $RCSfile: omiBSIM4SortParam.c,v $ */

