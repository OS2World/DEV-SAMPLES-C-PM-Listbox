#------------------------------------------------------------------------------
#
# ic.mak
#
# CPPFLAGS=-DIC_DEVELOP -Gm+ -Ge+ -Gd+ -O- -Ti+ -Tl- -Q+ -Ft- -Fi+ -Si+ -c
CPPFLAGS=-DIC_DEVELOP -Gm+ -Ge+ -Gd+ -O+ -Tl- -Q+ -Ft- -Fi+ -Si+ -c
# LFLAGS=/DEBUG /MAP
LFLAGS=

OBJECTLIST  = ic.obj

all:	   ic

ic:	   ic.exe

#--------------------------------------------------------------------------
# Building of ic.exe
#--------------------------------------------------------------------------
ic.exe:  \
  ic.obj
  icc.exe @<<
      -Tdp -I$(INCLUDE) -B"$(LFLAGS)" -Fe ic.exe
      $**
      dde4cci.lib dde4muii.lib xlistbox.lib
      ic.def
<<

{.}.cpp.obj:
   ICC.EXE $(CPPFLAGS)	.\$*.cpp

ic.OBJ:  ic.cpp ic.hpp ic.h xlistbox.hpp xlisthdr.hpp xlistevt.hpp
