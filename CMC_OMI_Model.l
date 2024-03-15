*************************************************
.LIB Demo
.option omiflag=1.10 modmonte=1 omipath='code/lib' omisave=1
.param  
*** Age ***
+dagetime   = 0 
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

.model nch_mac nmos (
+level      = 72
*
+omimodel   = 1
+omimod     = 1

*** Age
+agemod     = 1
+fvth0_age  = 1
+dagetime   = 'dagetime' 
***********Level 2 BTI model parameters
+a0 = 0.1 b0=5.0 c0=1.0 ea0=0.026 d0=1.0 nox=0.17
)
.model pch_mac PMOS ( 
+level      = 72
+omimodel   = 1
+omimod     = 1
*** Age
+agemod   = 2
+fvth0_age  = -1
+dagetime   = 'dagetime' 


)

.ENDL MOS
