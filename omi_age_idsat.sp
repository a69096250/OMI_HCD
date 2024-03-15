***************************
.option  nomod ingold=2 
+        newtol numdgt=7 relmos=1e-4 absmos=1e-8 relv=1e-4 relvdc=1e-4
.option MODSRH=0
.option  scale=1 
*----------------------------------------------------------
.temp 27
.option post 2

.option brief=1
.lib 'CMC_OMI_Model.l' Demo
.lib 'CMC_OMI_Model.l' Age_Demo
.option brief=0
.param dagetime = 0.0
Vss s 0 0.000
Vbs b 0 0.000

Vgs0 g0 0 1.000
Vds0 d0 0 1.000
mdut0 d0 g0 s b nch_mac w=1u l=1u

Vgs1 g1 0 -1.000
Vds1 d1 0 -1.000
*mdut1 d1 g1 s b pch_mac w=1u l=1u

.op
.tran 1e-6 3e-6

.alter
.param dagetime = 1e8
.end

