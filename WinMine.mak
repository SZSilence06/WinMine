# Microsoft Developer Studio Generated NMAKE File, Based on WinMine.dsp
!IF $(CFG)" == "
CFG=WinMine - Win32 Debug
!MESSAGE No configuration specified. Defaulting to WinMine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WinMine - Win32 Release" && "$(CFG)" != "WinMine - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinMine.mak" CFG="WinMine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinMine - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinMine - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "WinMine - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\WinMine.exe"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WinMine.obj"
	-@erase "$(INTDIR)\WinMine.pch"
	-@erase "$(INTDIR)\WinMine.res"
	-@erase "$(INTDIR)\WinMineDoc.obj"
	-@erase "$(INTDIR)\WinMineView.obj"
	-@erase "$(OUTDIR)\WinMine.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WinMine.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WinMine.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WinMine.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\WinMine.pdb" /machine:I386 /out:"$(OUTDIR)\WinMine.exe" 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WinMine.obj" \
	"$(INTDIR)\WinMineDoc.obj" \
	"$(INTDIR)\WinMineView.obj" \
	"$(INTDIR)\WinMine.res"

"$(OUTDIR)\WinMine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\WinMine.exe" "$(OUTDIR)\WinMine.bsc"


CLEAN :
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WinMine.obj"
	-@erase "$(INTDIR)\WinMine.pch"
	-@erase "$(INTDIR)\WinMine.res"
	-@erase "$(INTDIR)\WinMine.sbr"
	-@erase "$(INTDIR)\WinMineDoc.obj"
	-@erase "$(INTDIR)\WinMineDoc.sbr"
	-@erase "$(INTDIR)\WinMineView.obj"
	-@erase "$(INTDIR)\WinMineView.sbr"
	-@erase "$(OUTDIR)\WinMine.bsc"
	-@erase "$(OUTDIR)\WinMine.exe"
	-@erase "$(OUTDIR)\WinMine.ilk"
	-@erase "$(OUTDIR)\WinMine.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WinMine.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\WinMine.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\WinMine.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WinMine.sbr" \
	"$(INTDIR)\WinMineDoc.sbr" \
	"$(INTDIR)\WinMineView.sbr"

"$(OUTDIR)\WinMine.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\WinMine.pdb" /debug /machine:I386 /out:"$(OUTDIR)\WinMine.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WinMine.obj" \
	"$(INTDIR)\WinMineDoc.obj" \
	"$(INTDIR)\WinMineView.obj" \
	"$(INTDIR)\WinMine.res"

"$(OUTDIR)\WinMine.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("WinMine.dep")
!INCLUDE "WinMine.dep"
!ELSE 
!MESSAGE Warning: cannot find "WinMine.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "WinMine - Win32 Release" || "$(CFG)" == "WinMine - Win32 Debug"
SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "WinMine - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "WinMine - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\WinMine.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\WinMine.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\WinMine.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\WinMine.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WinMine.cpp

!IF  "$(CFG)" == "WinMine - Win32 Release"


"$(INTDIR)\WinMine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"


"$(INTDIR)\WinMine.obj"	"$(INTDIR)\WinMine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ENDIF 

SOURCE=.\WinMine.rc

"$(INTDIR)\WinMine.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\WinMineDoc.cpp

!IF  "$(CFG)" == "WinMine - Win32 Release"


"$(INTDIR)\WinMineDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"


"$(INTDIR)\WinMineDoc.obj"	"$(INTDIR)\WinMineDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ENDIF 

SOURCE=.\WinMineView.cpp

!IF  "$(CFG)" == "WinMine - Win32 Release"


"$(INTDIR)\WinMineView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ELSEIF  "$(CFG)" == "WinMine - Win32 Debug"


"$(INTDIR)\WinMineView.obj"	"$(INTDIR)\WinMineView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\WinMine.pch"


!ENDIF 


!ENDIF 

