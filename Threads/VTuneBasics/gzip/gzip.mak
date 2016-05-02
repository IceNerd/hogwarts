# Microsoft Developer Studio Generated NMAKE File, Based on gzip.dsp
!IF "$(CFG)" == ""
CFG=gzip - Win32 Debug
!MESSAGE No configuration specified. Defaulting to gzip - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "gzip - Win32 Release" && "$(CFG)" != "gzip - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gzip.mak" CFG="gzip - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gzip - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gzip - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "gzip - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\gzip.exe"


CLEAN :
	-@erase "$(INTDIR)\bits.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\gzip.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\lzw.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\unlzh.obj"
	-@erase "$(INTDIR)\unlzw.obj"
	-@erase "$(INTDIR)\unpack.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "$(OUTDIR)\gzip.exe"
	-@erase "$(OUTDIR)\gzip.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\gzip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gzip.bsc" 
BSC32_SBRS= \
	
LINK32=xilink6.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\gzip.pdb" /debug /machine:I386 /out:"$(OUTDIR)\gzip.exe" /fixed:no 
LINK32_OBJS= \
	"$(INTDIR)\bits.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\gzip.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\lzw.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\unlzh.obj" \
	"$(INTDIR)\unlzw.obj" \
	"$(INTDIR)\unpack.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\zip.obj"

"$(OUTDIR)\gzip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gzip - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\gzip.exe"


CLEAN :
	-@erase "$(INTDIR)\bits.obj"
	-@erase "$(INTDIR)\crypt.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\gzip.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\lzw.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\unlzh.obj"
	-@erase "$(INTDIR)\unlzw.obj"
	-@erase "$(INTDIR)\unpack.obj"
	-@erase "$(INTDIR)\unzip.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\zip.obj"
	-@erase "$(OUTDIR)\gzip.exe"
	-@erase "$(OUTDIR)\gzip.ilk"
	-@erase "$(OUTDIR)\gzip.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\gzip.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gzip.bsc" 
BSC32_SBRS= \
	
LINK32=xilink6.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\gzip.pdb" /debug /machine:I386 /out:"$(OUTDIR)\gzip.exe" /pdbtype:sept /fixed:no 
LINK32_OBJS= \
	"$(INTDIR)\bits.obj" \
	"$(INTDIR)\crypt.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\gzip.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\lzw.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\unlzh.obj" \
	"$(INTDIR)\unlzw.obj" \
	"$(INTDIR)\unpack.obj" \
	"$(INTDIR)\unzip.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\zip.obj"

"$(OUTDIR)\gzip.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("gzip.dep")
!INCLUDE "gzip.dep"
!ELSE 
!MESSAGE Warning: cannot find "gzip.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "gzip - Win32 Release" || "$(CFG)" == "gzip - Win32 Debug"
SOURCE=.\bits.c

"$(INTDIR)\bits.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\crypt.c

"$(INTDIR)\crypt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\deflate.c

"$(INTDIR)\deflate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\getopt.c

"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\gzip.c

"$(INTDIR)\gzip.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\inflate.c

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\lzw.c

"$(INTDIR)\lzw.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\trees.c

"$(INTDIR)\trees.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\unlzh.c

"$(INTDIR)\unlzh.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\unlzw.c

"$(INTDIR)\unlzw.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\unpack.c

"$(INTDIR)\unpack.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\unzip.c

"$(INTDIR)\unzip.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\util.c

"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\zip.c

"$(INTDIR)\zip.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

