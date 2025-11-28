*************************************************
.LIB Demo
.option omiflag=1.10 modmonte=1 omipath='code/lib' omisave=1
.param  
*** Age ***
+dagetime   = 0 
+random1=AGAUSS(0,1,1) random2=AGAUSS(0,1,1)
+par1=random1 par2=random2
+parl1 =AGAUSS(0,1,1) parl2 =AGAUSS(0,1,1)
+toxn           = 1.800e-09     dxln           = 1e-09         dxwn           = -5e-09        
+dvthn          = 0.008         dlvthn         = 1.2e-09       dwvthn         = 1.5e-09       
+dpvthn         = 1.3e-16       du0n           = 0.0005        dlu0n          = 2e-11         
+dwu0n          = 0             dpu0n          = 0             dvsatn         = 0             
+dlvsatn        = 0.00125       dwvsatn        = 0             dpvsatn        = 0 
+dxln_global='par1*5.0e-010'
+dxwn_global='par2*2.5e-009'
+toxp           = 1.80e-09      dxlp           = 1e-09         dxwp           = -5e-09        
+dvthp          = -0.018        dlvthp         = -1e-09        dwvthp         = -1.3e-09      
+dpvthp         = -1.7e-16      du0p           = 0             dlu0p          = -2.5e-11      
+dwu0p          = -4e-11        dpu0p          = -3e-18        dvsatp         = 0             
+dlvsatp        = 0.0008        dwvsatp        = 0             dpvsatp        = 4.5e-11       
+dxlp_global='par1*3.0e-010'
+dxwp_global='par2*1.0e-009'
.lib 'CMC_OMI_Model.l' MOS
.ENDL Demo

.LIB Age_Demo
.option omiAge=1
.option omiInput='omi.cfg'
.ENDL Age_Demo

**********************************************************************************************
*
.LIB MOS
**********************************************************************************************
*                                                                                            *
*                               NMOS DEVICE MODELS                                           *
*                                                                                            *
**********************************************************************************************
**********************************
*       Macro   model            *
**********************************

.model nch_mac.global nmos (
+omimodel   = 1
+omimod     = 1
+level      = 54
+BINUNIT    = 2                          PARAMCHK   = 1                          MOBMOD     = 0
+CAPMOD     = 2                          IGCMOD     = 1                          IGBMOD     = 1
+DIOMOD     = 1                          RDSMOD     = 0                          RBODYMOD   = 0
+RGATEMOD   = 1                          PERMOD     = 1                          ACNQSMOD   = 0
+TRNQSMOD   = 0                          TEMPMOD    = 0                          TNOM       = 25
+TOXE       = 1.80e-009                  TOXM       = 1.8e-009                   DTOX       = 8e-010
+EPSROX     = 3.9                        WINT       = 0                          LINT       = 0
+LL         = 0                          WL         = 0                          LLN        = 1
+WLN        = 1                          LW         = 0                          WW         = 0
+LWN        = 1                          WWN        = 1                          LWL        = 0
+WWL        = 0                          LLC        = 0                          WLC        = 0
+LWC        = 0                          WWC        = 0                          LWLC       = 0
+WWLC       = 0                          XL         = -4e-009                    XW         = 6e-009
+DLC        = 2.5e-009                   DWC        = 0                          XPART      = 1
+TOXREF     = 1.4e-009                   DLCIG      = 2.5e-009                   
+K2         = 0.05                       K3         = 0
+K3B        = 0                          W0         = 2.5e-006                   DVT0       = 1.8
+DVT1       = 0.52                       DVT2       = -0.032                     DVT0W      = 0
+DVT1W      = 0                          DVT2W      = 0                          DSUB       = 2
+MINV       = 0.05                       VOFFL      = 0                          DVTP0      = 1e-007
+DVTP1      = 0                          LPE0       = 5.75e-008                  LPEB       = 2.3e-010
+XJ         = 2e-008                     NGATE      = 5e+020                     NDEP       = 2.8e+018
+NSD        = 1e+020                     PHIN       = 0                          CDSC       = 0.0002
+CDSCB      = 0                          CDSCD      = 0                          CIT        = 0
+VOFF       = -0.15                      ETA0       = 0.05
+ETAB       = 0                          UD         = 0                          LUD        = 0
+WUD        = 0                          PUD        = 0
+UA         = 5e-011                     UB         = 3.5e-018                   UC         = -3e-011
+VSAT       = 115000                     AGS        = 1e-020
+A1         = 0                          A2         = 1                          B0         = -1e-020
+B1         = 0                          KETA       = 0.04                       DWG        = 0
+DWB        = 0                          PDIBLC1    = 0.028
+PDIBLC2    = 0.022                      PDIBLCB    = -0.005                     DROUT      = 0.45
+PVAG       = 1e-020                     DELTA      = 0.0075956                  PSCBE1     = 1e+009
+PSCBE2     = 1e-020                     FPROUT     = 0.2                        PDITS      = 0.2
+PDITSD     = 0.23                       PDITSL     = 2300000                    RSH        = 0
+RDSW       = 50                         PRWG       = 0                          PRWB       = 0
+WR         = 1                          ALPHA0     = 0.074                      ALPHA1     = 0.005
+BETA0      = 30                         AGIDL      = 0.0001                     BGIDL      = 2.1e+009
+CGIDL      = 0.0001                     EGIDL      = 0.8                        AIGBACC    = 0.012
+BIGBACC    = 0.0028                     CIGBACC    = 0.002                      NIGBACC    = 1
+AIGBINV    = 0.014                      BIGBINV    = 0.004                      CIGBINV    = 0.004
+EIGBINV    = 1.1                        NIGBINV    = 3                          AIGC       = 0.012
+BIGC       = 0.0028                     CIGC       = 0.002                      AIGSD      = 0.012
+BIGSD      = 0.0028                     CIGSD      = 0.002                      NIGC       = 1
+POXEDGE    = 1                          PIGCD      = 1                          NTOX       = 1
+XRCRG1     = 12                         XRCRG2     = 5                          VFBSDOFF   = 0.01
+LVFBSDOFF  = 0                          WVFBSDOFF  = 0                          PVFBSDOFF  = 0
+CGSO       = 6.238e-010                 CGDO       = 6.238e-010                 CGBO       = 0
+CGDL       = 2.495e-010                 CGSL       = 2.495e-010                 CLC        = 1e-007
+CLE        = 0.6                        CF         = 1.1e-010                   CKAPPAS    = 0.03
+CKAPPAD    = 0.03                       ACDE       = 1                          MOIN       = 15
+NOFF       = 0.9                        VOFFCV     = -0.02                      TVOFF      = 0
+LTVOFF     = 0                          WTVOFF     = 0                          PTVOFF     = 0
+TVFBSDOFF  = 0                          LTVFBSDOFF = 0                          WTVFBSDOFF = 0
+PTVFBSDOFF = 0                          KT1        = -0.37                      KT1L       = 0
+KT2        = -0.042                     UTE        = -1.5                       UA1        = 1e-009
+UB1        = -3.5e-019                  UC1        = 0                          PRT        = 0
+AT         = 53000                      
+JSS        = 0.0000                     JSD        = 0.0000              
+JSWS       = 0.0000                     JSWD       = 0.0000                     JSWGS      = 0.0000              
+JSWGD      = 0.0000                     NJS        = 1.02                       NJD        = 1.02                
+IJTHSFWD   = 0.01                       IJTHDFWD   = 0.01                       IJTHSREV   = 0.01                
+IJTHDREV   = 0.01                       BVS        = 10                         BVD        = 10                  
+XJBVS      = 1                          XJBVD      = 1                          JTSSWGS    = 0.0000              
+JTSSWGD    = 0.0000                     NJTSSWG    = 4                          XTSSWGS    = 0.02                
+XTSSWGD    = 0.02                       TNJTSSWG   = 1                          VTSSWGS    = 10                  
+VTSSWGD    = 10                         PBS        = 1                          PBD        = 1                   
+CJS        = 0.0000                     CJD        = 0.0000                     MJS        = 0.0                 
+MJD        = 0.0                        PBSWS      = 1                          PBSWD      = 1                   
+CJSWS      = 0.0000                     CJSWD      = 0.0000                     MJSWS      = 0.00                
+MJSWD      = 0.00                       PBSWGS     = 1                          PBSWGD     = 1                   
+CJSWGS     = 0.0000                     CJSWGD     = 0.0000                     MJSWGS     = 0.00                
+MJSWGD     = 0.00                       TPB        = 0.000                      TCJ        = 0.000               
+TPBSW      = 0.000                      TCJSW      = 0.000                      TPBSWG     = 0.000               
+TCJSWG     = 0.000                      XTIS       = 3                          XTID       = 3
+DMCG       = 3e-008                     DMCI       = 3e-008                     DMDG       = 0
+DMCGT      = 0                          DWJ        = 0                          XGW        = 0
+XGL        = -1e-009                    RSHG       = 0.4                        GBMIN      = 1e-010
+RBPB       = 50                         RBPD       = 50                         RBPS       = 50
+RBDB       = 50                         RBSB       = 50                         NGCON      = 1
+LVSAT      = 0                          PVSAT      = 0                          WVSAT      = 0

+delvto     = 0
+mulu0      = 1
+parl1      = 'parl1'                    parl2      = 'parl2'
*
*** statistical/corner parameters
*
+tox_c      = 'toxn'                     dxl_c      = 'dxln'
+dxw_c      = 'dxwn'                     dvth_c     = 'dvthn'                    dlvth_c    = 'dlvthn'
+dwvth_c    = 'dwvthn'                   dpvth_c    = 'dpvthn'                   du0_c      = 'du0n'
+dlu0_c     = 'dlu0n'                    dwu0_c     = 'dwu0n'                    dpu0_c     = 'dpu0n'
+dvsat_c    = 'dvsatn'                   dlvsat_c   = 'dlvsatn'                  dwvsat_c   = 'dwvsatn'
+dpvsat_c   = 'dpvsatn'
+dxl_g      = 'dxln_global'              dxw_g      = 'dxwn_global'
*
*
+mis_a_1    = 5.0e-010
+mis_a_2    = 2.5e-009
*
*** LOD 

+saref0    = 0.261e-6                    sbref0    = 0.261e-6
+wlod0     = 0
+ku00      = -2.0e-8                     lku00     = 3.0e-7                      wku00     = 1.0e-7
+pku00     = -1.0e-13                    tku00     = 0                           llodku00  = 1
+wlodku00  = 1                           kvsat0    = 0.2
+kvth00    = 3.5e-9                      lkvth00   = -2.0e-11                    wkvth00   = 0
+pkvth00   = 0                           llodvth0  = 1                           wlodvth0  = 1
+stk20     = 1.0e-9                      lodk20    = 0.5                         steta00   = 0
+lodeta00  = 1

+_tcj      = '0.001'                     _tcjsw    = '0.001'                     _tcjswg   = '0.005'  
+_tpb      = '0.005'                     _tpbsw    = '0.005'                     _tpbswg   = '0.001' 
+
+
+_xtis     = '3'                         _njs      = '1.02'                      _xjbvs    = '1'                        _bvs      = '10'
+_mjs      = '0.5'                       _mjsws    = '0.33'                      _mjswgs   = '0.33'
+_jss      = '0.0001'                    _jsws     = '1e-011'                    _jswgs    = '1e-010'
+_jtss     = '0.0'                       _jtssws   = '0.0'                       _jtsswgs  = '1e-07'
+
+_njts     = '20'                        _njtssw   = '20'                        _njtsswg  = '6'
+_njtsdx   = '20'                        _njtsswdx = '20'                        _njtsswgdx= '6'
+_tnjts    = '0'                         _tnjtssw  = '0'                         _tnjtsswg = '1'
+_vtss     = '10'                        _vtssws   = '10'                        _vtsswgs  = '10'
+_xtss     = '0.02'                      _xtssws   = '0.02'                      _xtsswgs  = '0.02'
+
+_pbs      = '1'                         _pbsws    = '1'                         _pbswgs   = '1'
+_cjs      = '0.0005'                    _cjsws    = '5e-010'                    _cjswgs   = '3e-010'
+
+
+_xtid     = '3'                         _njd      = '1.02'                      _xjbvd    = '1'                        _bvd      = '10'
+_mjd      = '0.5'                       _mjswd    = '0.33'                      _mjswgd   = '0.33'
+_jsd      = '0.0001'                    _jswd     = '1e-011'                    _jswgd    = '1e-010'
+_jtsd     = '0.0'                       _jtsswd   = '0.0'                       _jtsswgd  = '1e-07'
+
+_njtsd    = '20'                        _njtsswd  = '20'                        _njtsswgd = '6'
+_tnjtsd   = '0'                         _tnjtsswd = '0'                         _tnjtsswgd= '1'
+_vtsd     = '10'                        _vtsswd   = '10'                        _vtsswgd  = '10'
+_xtsd     = '0.02'                      _xtsswd   = '0.02'                      _xtsswgd  = '0.02'
+
+_pbd      = '1'                         _pbswd    = '1'                         _pbswgd   = '1'
+_cjd      = '0.0005'                    _cjswd    = '5e-010'                    _cjswgd   = '3e-010'
+
+_dwj      = '0'                         _wlc      = '0'                         _wln      = '1'  
+_wwc      = '0'                         _wwn      = '1'                         _wwlc     = '0'

+rn0xb     = 100

*** Age

+agemod     = 1
+fvth0_age  = 1
+dagetime   = 'dagetime' 
+Vgsdmax    = 5 
+n_age      = 0.44           		 Hs_age         = 1             	 ms_age         = 3       
+Hg_age     = 1             		 mg_age         = 3 
)

.model nch_mac.1 NMOS ( 
+LEVEL      = 54                         LMIN       = 2.16e-007                  LMAX       = 9.01e-06
+WMIN       = 9e-007                     WMAX       = 9.01e-06                   VERSION    = 4.5
+VTH0       = 0.39565768
+LVTH0      = -1.1852957e-009            WVTH0      = 4.3454056e-008             PVTH0      = -2.8432265e-014
+K1         = 0.40244047                 LK1        = -2.1954507e-008            WK1        = -2.4311886e-010
+PK1        = 2.1870973e-015
+NFACTOR    = 0.80689813                 LNFACTOR   = 3.8566337e-008
+WNFACTOR   = -1.0559616e-007            PNFACTOR   = 4.3741946e-014
+U0         = 0.039821866
+LU0        = -4.0994826e-010            WU0        = 2.0389874e-009             PU0        = -2.1870973e-016
+A0         = 1.0111128                  LA0        = 1.0127282e-007
+WA0        = -2.0876112e-007            PA0        = 6.5612919e-014
+PCLM       = 0.08
*
**** dynamic bin flags
+lmin_flag  = 1                          lmax_flag  = 0                          wmin_flag  = 1
+wmax_flag  = 0
*
**** general setting 
*
+omimodel           = 1
*
 )

.model nch_mac.2 NMOS ( 
+LEVEL      = 54                         LMIN       = 3.78e-08                   LMAX       = 2.16e-007
+WMIN       = 9e-007                     WMAX       = 9.01e-06                   VERSION    = 4.5
+VTH0       = 0.4168459
+LVTH0      = -5.6771973e-009            WVTH0      = -1.0976703e-007            PVTH0      = 4.0506058e-015
+K1         = 0.2891856                  LK1        = 2.0555267e-009             WK1        = 1.1984041e-008
+PK1        = -4.0506058e-016
+NFACTOR    = 0.95300146                 LNFACTOR   = 7.5924323e-009
+WNFACTOR   = 8.1627147e-008             PNFACTOR   = 4.0506058e-015
+U0         = 0.038962549
+LU0        = -2.2777297e-010            WU0        = 1.5805367e-009             PU0        = -1.2151818e-016
+A0         = 1.3876129                  LA0        = 2.1454802e-008
+WA0        = 1.5805367e-007             PA0        = -1.2151818e-014
+PCLM       = 0.080424309                LPCLM      = -8.9953494e-011
+WPCLM      = -3.8213263e-009            PPCLM      = 8.1012117e-016
*
**** dynamic bin flags
+lmin_flag  = 0                          lmax_flag  = 1                          wmin_flag  = 1
+wmax_flag  = 0
*
**** general setting 
*
+omimodel           = 1
*
 )

.model nch_mac.3 NMOS ( 
+LEVEL      = 54                         LMIN       = 2.16e-007                  LMAX       = 9.01e-06
+WMIN       = 0.54e-06                   WMAX       = 9e-007                     VERSION    = 4.5
+VTH0       = 0.46208128
+LVTH0      = -6.2203899e-008            WVTH0      = -1.6725725e-008            PVTH0      = 2.685059e-014
+K1         = 0.401074                   LK1        = -9.6616876e-009            WK1        = 9.9490847e-010
+PK1        = -8.9501966e-015
+NFACTOR    = 0.84201275                 LNFACTOR   = 8.684663e-008
+WNFACTOR   = -1.3741e-007               PNFACTOR   = -6.2996012e-029
+U0         = 0.039075676
+LU0        = -9.806432e-010             WU0        = 2.7150364e-009             PU0        = 2.9833989e-016
+A0         = 0.93967972                 LA0        = 1.0783457e-007
+WA0        = -1.4404272e-007            PA0        = 5.9667977e-014
+PCLM       = 0.08
*
**** dynamic bin flags
+lmin_flag  = 1                          lmax_flag  = 0                          wmin_flag  = 0
+wmax_flag  = 1
*
**** general setting 
*
+omimodel           = 1
*
 )

.model nch_mac.4 NMOS ( 
+LEVEL      = 54                         LMIN       = 3.78e-08                   LMAX       = 2.16e-007
+WMIN       = 0.54e-06                   WMAX       = 9e-007                     VERSION    = 4.5
+VTH0       = 0.15421979
+LVTH0      = 3.0627378e-009             WVTH0      = 1.2817222e-007             PVTH0      = -3.8677754e-015
+K1         = 0.35654321                 LK1        = -2.2116049e-010            WK1        = -4.9041953e-008
+PK1        = 1.657618e-015
+NFACTOR    = 1.3098335                  LNFACTOR   = -1.2331373e-008
+WNFACTOR   = -2.4166271e-007            PNFACTOR   = 2.2101573e-014
+U0         = 0.035006379
+LU0        = -1.1795226e-010            WU0        = 5.1648271e-009             PU0        = -2.2101573e-016
+A0         = 1.3528638                  LA0        = 2.0239536e-008
+WA0        = 1.8953635e-007             PA0        = -1.1050787e-014
+PCLM       = 0.08195997                 LPCLM      = -4.1551366e-010
+WPCLM      = -5.2126352e-009            PPCLM      = 1.1050787e-015
*
**** dynamic bin flags
+lmin_flag  = 0                          lmax_flag  = 1                          wmin_flag  = 0
+wmax_flag  = 1
*
**** general setting 
*
+omimodel           = 1
*
 )


.ENDL MOS
