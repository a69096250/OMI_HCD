/*
 *************************************************
 *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
 *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
 *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
 *  included with this distribution for usage terms and conditions.
 *************************************************
 *  File        : omiBSIM4Def.h
 *  Date        : 2010_1123
 *  Description : BSIM4 data structures
 */


#include "omiDef.h"
#include "omiBinTree.h"
#include "omiHash.h"
#include "omiAge.h"


#define pwr(A, B) ((A) >= 0 ? pow(fabs(A), B) : (-1 * pow(fabs(A),B)))
#define min(A, B) ((A) > (B) ? (B) : (A))
#define max(A, B) ((A) > (B) ? (A) : (B))
#define abs(A)     ((A) >= 0 ? (A) : -(A))

#define TRUE 1
#define PARAM_LEN 16


typedef struct omiBSIM4Model
{
  /* OMI model parameters and paramGiven flags */
  int     modelType;
  int     printModel;

  /* Corner skew parameter */
  double tox_c, tox_g, tox_max, tox_min;
  double dxl_c, dxl_g, dxl_max, dxl_min;
  double dxw_c, dxw_g, dxw_max, dxw_min;
  double dvth_c, dvth_g, dvth_max, dvth_min;
  double dlvth_c, dlvth_g, dlvth_max, dlvth_min;
  double dwvth_c, dwvth_g, dwvth_max, dwvth_min;
  double dpvth_c, dpvth_g, dpvth_max, dpvth_min;
  double du0_c, du0_g, du0_max, du0_min;
  double dlu0_c, dlu0_g, dlu0_max, dlu0_min;
  double dwu0_c, dwu0_g, dwu0_max, dwu0_min;
  double dpu0_c, dpu0_g, dpu0_max, dpu0_min;
  double dvsat_c, dvsat_g, dvsat_max, dvsat_min;
  double dlvsat_c, dlvsat_g, dlvsat_max, dlvsat_min;
  double dwvsat_c, dwvsat_g, dwvsat_max, dwvsat_min;
  double dpvsat_c, dpvsat_g, dpvsat_max, dpvsat_min;

  /* instance / setup lib relate model parameter */
  double delvto,mulu0;

  /* ratio parameter */
  double mis_a_1,mis_a_2;

  /* local parameter */
  double parl1,parl2;

  /* layout_dependence_parameters */
  double saref0,sbref0,wlod0,ku00,lku00;
  double wku00,pku00,tku00,llodku00,wlodku00;
  double kvsat0,kvth00,lkvth00,wkvth00,pkvth00;
  double llodvth0,wlodvth0,stk20,lodk20,steta00;
  double lodeta00;

  /* external_Rn0xb_parameter */
  double rn0xb;

  /* external_junction_diode_parameter */
  double _tcj,_tcjsw,_tcjswg,_tpb,_tpbsw;
  double _tpbswg,_xtis,_njs,_bvs,_mjs;
  double _mjsws,_mjswgs,_jss,_jsws,_jswgs;
  double _jtss,_jtssws,_jtsswgs,_njts,_njtssw;
  double _njtsswg,_njtsdx,_njtsswdx,_njtsswgdx,_tnjts;
  double _tnjtssw,_tnjtsswg,_vtss,_vtssws,_vtsswgs;
  double _xtss,_xtssws,_xtsswgs,_pbs,_pbsws;
  double _pbswgs,_cjs,_cjsws,_cjswgs,_xtid;
  double _njd,_mjd,_mjswd,_mjswgd,_jsd;
  double _jswd,_jswgd,_jtsd,_jtsswd,_jtsswgd;
  double _tnjtsd,_tnjtsswd,_tnjtsswgd,_vtsd,_vtsswd;
  double _vtsswgd,_xtsd,_xtsswd,_xtsswgd,_pbd;
  double _pbswd,_pbswgd,_cjd,_cjswd,_cjswgd;
  double _dwj,_wlc,_wln,_wwc,_wwn;
  double _wwlc;

  /* OMI_flow_switch_parameter */
  double omimod;

  /* Age_model_parameter */
  int agemod;
  double fvth0_age,dagetime,n_age,Hs_age;
  double ms_age,Hg_age,mg_age;

  /* SOA_model_parameter */
  double Vgsdmax;

/***************************/

  unsigned tox_cGiven:1, tox_gGiven:1, tox_maxGiven:1, tox_minGiven:1;
  unsigned dxl_cGiven:1, dxl_gGiven:1, dxl_maxGiven:1, dxl_minGiven:1;
  unsigned dxw_cGiven:1, dxw_gGiven:1, dxw_maxGiven:1, dxw_minGiven:1;
  unsigned dvth_cGiven:1, dvth_gGiven:1, dvth_maxGiven:1, dvth_minGiven:1;
  unsigned dlvth_cGiven:1, dlvth_gGiven:1, dlvth_maxGiven:1, dlvth_minGiven:1;
  unsigned dwvth_cGiven:1, dwvth_gGiven:1, dwvth_maxGiven:1, dwvth_minGiven:1;
  unsigned dpvth_cGiven:1, dpvth_gGiven:1, dpvth_maxGiven:1, dpvth_minGiven:1;
  unsigned du0_cGiven:1, du0_gGiven:1, du0_maxGiven:1, du0_minGiven:1;
  unsigned dlu0_cGiven:1, dlu0_gGiven:1, dlu0_maxGiven:1, dlu0_minGiven:1;
  unsigned dwu0_cGiven:1, dwu0_gGiven:1, dwu0_maxGiven:1, dwu0_minGiven:1;
  unsigned dpu0_cGiven:1, dpu0_gGiven:1, dpu0_maxGiven:1, dpu0_minGiven:1;
  unsigned dvsat_cGiven:1, dvsat_gGiven:1, dvsat_maxGiven:1, dvsat_minGiven:1;
  unsigned dlvsat_cGiven:1, dlvsat_gGiven:1, dlvsat_maxGiven:1, dlvsat_minGiven:1;
  unsigned dwvsat_cGiven:1, dwvsat_gGiven:1, dwvsat_maxGiven:1, dwvsat_minGiven:1;
  unsigned dpvsat_cGiven:1, dpvsat_gGiven:1, dpvsat_maxGiven:1, dpvsat_minGiven:1;

  unsigned delvtoGiven:1,mulu0Given:1;

  unsigned mis_a_1Given:1,mis_a_2Given:1;

  unsigned parl1Given:1,parl2Given:1;

  unsigned saref0Given:1,sbref0Given:1,wlod0Given:1,ku00Given:1,lku00Given:1;
  unsigned wku00Given:1,pku00Given:1,tku00Given:1,llodku00Given:1,wlodku00Given:1;
  unsigned kvsat0Given:1,kvth00Given:1,lkvth00Given:1,wkvth00Given:1,pkvth00Given:1;
  unsigned llodvth0Given:1,wlodvth0Given:1,stk20Given:1,lodk20Given:1,steta00Given:1;
  unsigned lodeta00Given:1;

  unsigned rn0xbGiven:1;

  unsigned _tcjGiven:1,_tcjswGiven:1,_tcjswgGiven:1,_tpbGiven:1,_tpbswGiven:1;
  unsigned _tpbswgGiven:1,_xtisGiven:1,_njsGiven:1,_bvsGiven:1,_mjsGiven:1;
  unsigned _mjswsGiven:1,_mjswgsGiven:1,_jssGiven:1,_jswsGiven:1,_jswgsGiven:1;
  unsigned _jtssGiven:1,_jtsswsGiven:1,_jtsswgsGiven:1,_njtsGiven:1,_njtsswGiven:1;
  unsigned _njtsswgGiven:1,_njtsdxGiven:1,_njtsswdxGiven:1,_njtsswgdxGiven:1,_tnjtsGiven:1;
  unsigned _tnjtsswGiven:1,_tnjtsswgGiven:1,_vtssGiven:1,_vtsswsGiven:1,_vtsswgsGiven:1;
  unsigned _xtssGiven:1,_xtsswsGiven:1,_xtsswgsGiven:1,_pbsGiven:1,_pbswsGiven:1;
  unsigned _pbswgsGiven:1,_cjsGiven:1,_cjswsGiven:1,_cjswgsGiven:1,_xtidGiven:1;
  unsigned _njdGiven:1,_mjdGiven:1,_mjswdGiven:1,_mjswgdGiven:1,_jsdGiven:1;
  unsigned _jswdGiven:1,_jswgdGiven:1,_jtsdGiven:1,_jtsswdGiven:1,_jtsswgdGiven:1;
  unsigned _tnjtsdGiven:1,_tnjtsswdGiven:1,_tnjtsswgdGiven:1,_vtsdGiven:1,_vtsswdGiven:1;
  unsigned _vtsswgdGiven:1,_xtsdGiven:1,_xtsswdGiven:1,_xtsswgdGiven:1,_pbdGiven:1;
  unsigned _pbswdGiven:1,_pbswgdGiven:1,_cjdGiven:1,_cjswdGiven:1,_cjswgdGiven:1;
  unsigned _dwjGiven:1,_wlcGiven:1,_wlnGiven:1,_wwcGiven:1,_wwnGiven:1;
  unsigned _wwlcGiven:1;

  unsigned omimodGiven:1;

  unsigned agemodGiven:1,fvth0_ageGiven:1,dagetimeGiven:1,n_ageGiven:1,Hs_ageGiven:1;
  unsigned ms_ageGiven:1,Hg_ageGiven:1,mg_ageGiven:1;

  unsigned VgsdmaxGiven:1;


/***************************/

/* BSIM4 model parameters, which need to be updated in omiBSIM4Temp.c */
  double toxe;
  double xl;
  double xw;
  double vth0;
  double lvth0;
  double wvth0;
  double pvth0;
  double k2;
  double eta0;
  double u0;
  double lu0;
  double wu0;
  double pu0;
  double vsat;
  double lvsat;
  double wvsat;
  double pvsat;
  double dmci;
  double dmcg;
  double tnom;

  unsigned toxeGiven:1;
  unsigned xlGiven:1;
  unsigned xwGiven:1;
  unsigned vth0Given:1;
  unsigned lvth0Given:1;
  unsigned wvth0Given:1;
  unsigned pvth0Given:1;
  unsigned k2Given:1;
  unsigned eta0Given:1;
  unsigned u0Given:1;
  unsigned lu0Given:1;
  unsigned wu0Given:1;
  unsigned pu0Given:1;
  unsigned vsatGiven:1;
  unsigned lvsatGiven:1;
  unsigned wvsatGiven:1;
  unsigned pvsatGiven:1;
  unsigned dmciGiven:1;
  unsigned dmcgGiven:1;
  unsigned tnomGiven:1;

} omiBSIM4Model;

typedef struct omiBSIM4Instance
{
  /* OMI instance parameters and paramGiven flags */
  /* aging instance information */
  char *instName;
  omiSimpleAge *pSimpleAge;

  int printWarn;

  /* BSIM4 instance parameters, which need to be used in omiBSIM4Temp.c */
  double l;
  double w;
  double m;
  double nf;
  double ad;
  double as;
  double pd;
  double ps;
  double nrd;
  double nrs;
  double sa;
  double sb;
  double sd;
  double sca;
  double scb;
  double scc;
  double delvto;
  double mulu0;

  /* Flexible instance parameters, which need to be used in extCMIb4set.c */
  double multi,scale,_dmcg,_dmci,_xw;
  double _xl,_delvto,_mulu0,prnflag;

  /* external_junction_diode_parameter */
  double _vt , _vt_tnom , _eg_tnom , _eg , common0 , common1 , common2 ;
  double weffcj, _adeff, _aseff, _pdeff, _pseff;  
  double jtsswgs , jtssws , jtss , njtsswg , njtssw , njts , Isbs ;      
  double pbs , pbsws , pbswgs , cjs , cjsws , cjswgs ;        
  double jtsswgd , jtsswd , jtsd , njtsswgd , njtsswd , njtsd , Isbd ;      
  double pbd , pbswd , pbswgd , cjd , cjswd , cjswgd ;
  double xtis,xtid;

  unsigned lGiven:1;
  unsigned wGiven:1;
  unsigned mGiven:1;
  unsigned nfGiven:1;
  unsigned adGiven:1;
  unsigned asGiven:1;
  unsigned pdGiven:1;
  unsigned psGiven:1;
  unsigned nrdGiven:1;
  unsigned nrsGiven:1;
  unsigned saGiven:1;
  unsigned sbGiven:1;
  unsigned sdGiven:1;
  unsigned scaGiven:1;
  unsigned scbGiven:1;
  unsigned sccGiven:1;
  unsigned delvtoGiven:1;
  unsigned mulu0Given:1;

  unsigned multiGiven:1,scaleGiven:1,_dmcgGiven:1,_dmciGiven:1,_xwGiven:1;
  unsigned _xlGiven:1,_delvtoGiven:1,_mulu0Given:1;
  unsigned prnflagGiven:1;

} omiBSIM4Instance;


/* User can't use -1 (OMI_BADPARAM) for parameter ID */

/* Instance parameter */
#define B4_INST_SIZE_o  18  /* number of instance parameter (output) */

#define B4_INST_l             0
#define B4_INST_w             1
#define B4_INST_m             2
#define B4_INST_nf            3
#define B4_INST_ad            4
#define B4_INST_as            5
#define B4_INST_pd            6
#define B4_INST_ps            7
#define B4_INST_nrd           8
#define B4_INST_nrs           9
#define B4_INST_sa            10
#define B4_INST_sb            11
#define B4_INST_sd            12
#define B4_INST_sca           13
#define B4_INST_scb           14
#define B4_INST_scc           15
#define B4_INST_delvto        16
#define B4_INST_mulu0         17

#define B4_INST_multi         101
#define B4_INST_scale         102
#define B4_INST__dmcg         103
#define B4_INST__dmci         104
#define B4_INST__xw           105
#define B4_INST__xl           106
#define B4_INST__delvto       107
#define B4_INST__mulu0        108
#define B4_INST_prnflag       109


/* Model parameter */
#define B4_MOD_SIZE_o  20  /* number of model parameter (output) */

#define B4_MOD_toxe                           0
#define B4_MOD_xl                             1
#define B4_MOD_xw                             2
#define B4_MOD_vth0                           3
#define B4_MOD_lvth0                          4
#define B4_MOD_wvth0                          5
#define B4_MOD_pvth0                          6
#define B4_MOD_k2                             7
#define B4_MOD_u0                             8
#define B4_MOD_lu0                            9
#define B4_MOD_wu0                            10
#define B4_MOD_pu0                            11
#define B4_MOD_eta0                           12
#define B4_MOD_vsat                           13
#define B4_MOD_lvsat                          14
#define B4_MOD_wvsat                          15
#define B4_MOD_pvsat                          16
#define B4_MOD_dmci                           17
#define B4_MOD_dmcg                           18
#define B4_MOD_tnom                           19

#define B4_MOD_tox_c                          1001
#define B4_MOD_tox_g                          1002
#define B4_MOD_tox_max                        1003
#define B4_MOD_tox_min                        1004
#define B4_MOD_dxl_c                          1005
#define B4_MOD_dxl_g                          1006
#define B4_MOD_dxl_max                        1007
#define B4_MOD_dxl_min                        1008
#define B4_MOD_dxw_c                          1009
#define B4_MOD_dxw_g                          1010
#define B4_MOD_dxw_max                        1011
#define B4_MOD_dxw_min                        1012
#define B4_MOD_dvth_c                         1013
#define B4_MOD_dvth_g                         1014
#define B4_MOD_dvth_max                       1015
#define B4_MOD_dvth_min                       1016
#define B4_MOD_dlvth_c                        1017
#define B4_MOD_dlvth_g                        1018
#define B4_MOD_dlvth_max                      1019
#define B4_MOD_dlvth_min                      1020
#define B4_MOD_dwvth_c                        1021
#define B4_MOD_dwvth_g                        1022
#define B4_MOD_dwvth_max                      1023
#define B4_MOD_dwvth_min                      1024
#define B4_MOD_dpvth_c                        1025
#define B4_MOD_dpvth_g                        1026
#define B4_MOD_dpvth_max                      1027
#define B4_MOD_dpvth_min                      1028
#define B4_MOD_du0_c                          1029
#define B4_MOD_du0_g                          1030
#define B4_MOD_du0_max                        1031
#define B4_MOD_du0_min                        1032
#define B4_MOD_dlu0_c                         1033
#define B4_MOD_dlu0_g                         1034
#define B4_MOD_dlu0_max                       1035
#define B4_MOD_dlu0_min                       1036
#define B4_MOD_dwu0_c                         1037
#define B4_MOD_dwu0_g                         1038
#define B4_MOD_dwu0_max                       1039
#define B4_MOD_dwu0_min                       1040
#define B4_MOD_dpu0_c                         1041
#define B4_MOD_dpu0_g                         1042
#define B4_MOD_dpu0_max                       1043
#define B4_MOD_dpu0_min                       1044
#define B4_MOD_dvsat_c                        1045
#define B4_MOD_dvsat_g                        1046
#define B4_MOD_dvsat_max                      1047
#define B4_MOD_dvsat_min                      1048
#define B4_MOD_dlvsat_c                       1049
#define B4_MOD_dlvsat_g                       1050
#define B4_MOD_dlvsat_max                     1051
#define B4_MOD_dlvsat_min                     1052
#define B4_MOD_dwvsat_c                       1053
#define B4_MOD_dwvsat_g                       1054
#define B4_MOD_dwvsat_max                     1055
#define B4_MOD_dwvsat_min                     1056
#define B4_MOD_dpvsat_c                       1057
#define B4_MOD_dpvsat_g                       1058
#define B4_MOD_dpvsat_max                     1059
#define B4_MOD_dpvsat_min                     1060

#define B4_MOD_delvto                         1061
#define B4_MOD_mulu0                          1062
#define B4_MOD_mis_a_1                        1063
#define B4_MOD_mis_a_2                        1064
#define B4_MOD_parl1                          1065
#define B4_MOD_parl2                          1066
#define B4_MOD_saref0                         1071
#define B4_MOD_sbref0                         1072
#define B4_MOD_wlod0                          1073
#define B4_MOD_ku00                           1074
#define B4_MOD_lku00                          1075
#define B4_MOD_wku00                          1076
#define B4_MOD_pku00                          1077
#define B4_MOD_tku00                          1078
#define B4_MOD_llodku00                       1079
#define B4_MOD_wlodku00                       1080
#define B4_MOD_kvsat0                         1081
#define B4_MOD_kvth00                         1082
#define B4_MOD_lkvth00                        1083
#define B4_MOD_wkvth00                        1084
#define B4_MOD_pkvth00                        1085
#define B4_MOD_llodvth0                       1086
#define B4_MOD_wlodvth0                       1087
#define B4_MOD_stk20                          1088
#define B4_MOD_lodk20                         1089
#define B4_MOD_steta00                        1090
#define B4_MOD_lodeta00                       1091
#define B4_MOD_rn0xb                          1092
#define B4_MOD__tcj                           1093
#define B4_MOD__tcjsw                         1094
#define B4_MOD__tcjswg                        1095
#define B4_MOD__tpb                           1096
#define B4_MOD__tpbsw                         1097
#define B4_MOD__tpbswg                        1098
#define B4_MOD__xtis                          1099
#define B4_MOD__njs                           1100
#define B4_MOD__bvs                           1101
#define B4_MOD__mjs                           1102
#define B4_MOD__mjsws                         1103
#define B4_MOD__mjswgs                        1104
#define B4_MOD__jss                           1105
#define B4_MOD__jsws                          1106
#define B4_MOD__jswgs                         1107
#define B4_MOD__jtss                          1108
#define B4_MOD__jtssws                        1109
#define B4_MOD__jtsswgs                       1110
#define B4_MOD__njts                          1111
#define B4_MOD__njtssw                        1112
#define B4_MOD__njtsswg                       1113
#define B4_MOD__njtsdx                        1114
#define B4_MOD__njtsswdx                      1115
#define B4_MOD__njtsswgdx                     1116
#define B4_MOD__tnjts                         1117
#define B4_MOD__tnjtssw                       1118
#define B4_MOD__tnjtsswg                      1119
#define B4_MOD__vtss                          1120
#define B4_MOD__vtssws                        1121
#define B4_MOD__vtsswgs                       1122
#define B4_MOD__xtss                          1123
#define B4_MOD__xtssws                        1124
#define B4_MOD__xtsswgs                       1125
#define B4_MOD__pbs                           1126
#define B4_MOD__pbsws                         1127
#define B4_MOD__pbswgs                        1128
#define B4_MOD__cjs                           1129
#define B4_MOD__cjsws                         1130
#define B4_MOD__cjswgs                        1131
#define B4_MOD__xtid                          1132
#define B4_MOD__njd                           1133
#define B4_MOD__mjd                           1134
#define B4_MOD__mjswd                         1135
#define B4_MOD__mjswgd                        1136
#define B4_MOD__jsd                           1137
#define B4_MOD__jswd                          1138
#define B4_MOD__jswgd                         1139
#define B4_MOD__jtsd                          1140
#define B4_MOD__jtsswd                        1141
#define B4_MOD__jtsswgd                       1142
#define B4_MOD__tnjtsd                        1143
#define B4_MOD__tnjtsswd                      1144
#define B4_MOD__tnjtsswgd                     1145
#define B4_MOD__vtsd                          1146
#define B4_MOD__vtsswd                        1147
#define B4_MOD__vtsswgd                       1148
#define B4_MOD__xtsd                          1149
#define B4_MOD__xtsswd                        1150
#define B4_MOD__xtsswgd                       1151
#define B4_MOD__pbd                           1152
#define B4_MOD__pbswd                         1153
#define B4_MOD__pbswgd                        1154
#define B4_MOD__cjd                           1155
#define B4_MOD__cjswd                         1156
#define B4_MOD__cjswgd                        1157
#define B4_MOD__dwj                           1158
#define B4_MOD__wlc                           1159
#define B4_MOD__wln                           1160
#define B4_MOD__wwc                           1161
#define B4_MOD__wwn                           1162
#define B4_MOD__wwlc                          1163
#define B4_MOD_omimod                         1164
#define B4_MOD_agemod                         1165
#define B4_MOD_fvth0_age                      1166
#define B4_MOD_dagetime                       1167
#define B4_MOD_n_age                          1168
#define B4_MOD_Hs_age                         1169
#define B4_MOD_ms_age                         1170
#define B4_MOD_Hg_age                         1171
#define B4_MOD_mg_age                         1172
#define B4_MOD_Vgsdmax                        1173


extern String    omi_b4_inst_param_o[B4_INST_SIZE_o];
extern double  *omi_b4_inst_value_o;
extern String    omi_b4_mod_param_o[B4_MOD_SIZE_o];
extern double  *omi_b4_mod_value_o;
extern omiSelectModelBin *omi_b4_mod_bin;
extern parNode *omiBSIM4InstHeader;
extern parNode *omiBSIM4ModelHeader;


int    omiBSIM4InitModelParam (omiBSIM4Model *pBSIM4Model);
int    omiBSIM4AssignModelParam (omiModel *pModel, omiBSIM4Model *pBSIM4Model);
ParamId omiBSIM4GetModelParamIdByName (String aName);
int    omiBSIM4SetModelParam (omiBSIM4Model *pBSIM4Model, String aName, double aValue);
int    omiBSIM4SetModelParamDefault (omiBSIM4Model *pBSIM4Model);
int    omiBSIM4PrintModel (omiModel *pModel, omiBSIM4Model *pBSIM4Model);
int    omiBSIM4InitInstParam (omiBSIM4Instance *pBSIM4Inst);
int    omiBSIM4AssignInstParam (omiInstance *pInstance, omiBSIM4Instance *pBSIM4Inst);
ParamId omiBSIM4GetInstParamIdByName (String aName);
int    omiBSIM4SetInstParam (omiBSIM4Instance *pBSIM4Inst, String aName, double aValue);
int    omiBSIM4SetInstParamDefault (omiCKT *pCKT, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst);
int    omiBSIM4Temp (omiCKT *pCKT, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst);
int    omiBSIM4CheckModel (omiInstance *pInstance, omiBSIM4Model *pBSIM4Model, omiBSIM4Instance *pBSIM4Inst);
void     omiBSIM4BuildInstParam ();
void     omiBSIM4BuildModelParam ();
void    omiBSIM4RegroupInstParam (omiInstance *pInstance);

/* OMI register function */
void omiRegroupParamReg (omiInstance *pInstance);

/* This structure provides convenient access to the Core Data
   operating point variables/parameters used by OMI.
   Prior to OMI 1.1.0, it was defined in omiIft.h  */
typedef struct omiBSIM4CoreData
{
  double vth;
  double vdsat;
  double ids;
  double gds;
  double gm;
  double gmbs;
  double beta;
  double gamma;
  double ibs;
  double ibd;
  double isub;
  double igso;
  double igdo;
  double igb;
  double igcs;
  double igcd;
  double igidl;
  double igisl;
} omiBSIM4CoreData;

#define B4_CORE_DATA_SIZE  18  /* number of core data variables */
extern String  omi_b4_core_data_param[B4_CORE_DATA_SIZE];



/* end of $RCSfile: omiBSIM4Def.h,v $ */
