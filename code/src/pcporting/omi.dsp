# Microsoft Developer Studio Project File - Name="omi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=omi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "omi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "omi.mak" CFG="omi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "omi - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "omi - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "omi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\obj\WIN"
# PROP Intermediate_Dir "..\..\obj\WIN"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /O2 /I "..\..\include" /I "..\ut" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__STDC__" /D "_USRDLL" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /machine:I386 /def:".\omi.def" /out:"..\..\lib\WIN\libOMImodel.dll" /implib:"..\..\lib\WIN\libOMImodel.lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "omi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\obj\WIN_dbg"
# PROP Intermediate_Dir "..\..\obj\WIN_dbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /w /W0 /Gm /GX /ZI /Od /I "..\..\include" /I "..\ut" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__STDC__" /D "_USRDLL" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /def:".\omi.def" /out:"..\..\lib\WIN_dbg\libOMImodel.dll" /implib:"..\..\lib\WIN_dbg\libOMImodel.lib" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "omi - Win32 Release"
# Name "omi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "models"

# PROP Default_Filter ""
# Begin Group "bsim4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4BuildParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Def.h
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Eval.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4GetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4GetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Ift.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Ift.h
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4InitInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4InitModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Set.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4SetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4SetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsim4\omiBSIM4Temp.c
# End Source File
# End Group
# Begin Group "bsimcmg"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMG.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGBuildParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGDef.h
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGEval.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGGetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGGetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGIft.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGIft.h
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGInitInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGInitModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGSet.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGSetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGSetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimcmg\omiBSIMCMGTemp.c
# End Source File
# End Group
# Begin Group "hisim2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2BuildParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Def.h
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Eval.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2GetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2GetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Ift.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Ift.h
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2InitInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2InitModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Set.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2SetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2SetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\hisim2\omiHiSIM2Temp.c
# End Source File
# End Group
# Begin Group "bsimsoi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOI.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIBuildParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIDef.h
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIEval.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIGetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIGetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIIft.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIIft.h
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIInitInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOIInitModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOISet.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOISetInstParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOISetModelParam.c
# End Source File
# Begin Source File

SOURCE=..\models\bsimsoi\omiBSIMSOITemp.c
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\models\common\omiAge.h
# End Source File
# End Group
# End Group
# Begin Group "simif"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\simif\omiIft.c
# End Source File
# Begin Source File

SOURCE=..\simif\omiMain.c
# End Source File
# End Group
# Begin Group "ut"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ut\omiBinTree.c
# End Source File
# Begin Source File

SOURCE=..\ut\omiBinTree.h
# End Source File
# Begin Source File

SOURCE=..\ut\omiHash.c
# End Source File
# Begin Source File

SOURCE=..\ut\omiHash.h
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\omiDef.h
# End Source File
# Begin Source File

SOURCE=..\..\include\omiIft.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
