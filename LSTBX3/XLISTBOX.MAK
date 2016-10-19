.SUFFIXES:
.SUFFIXES: .c .h .cpp .hpp

# /B" /ALIGN:4 /EXEPACK /PACKCODE /PACKDATA /NOI /NOE /NOD /de /base:65536"
#  ICC.EXE /Tl- /Tdp /Ti /Gm+ /Gd+ /Ge- /Ft- /C   .\$*.cpp

OBJS = xlistbox.obj xlistini.obj xlisthdr.obj xlistevt.obj

xlistbox.DLL:  \
  $(OBJS)      \
  xlistbox.MAK
  CPPFILT -b -p $(OBJS) >filter.def
  copy header.def+filter.def xlistbox.def
  ICC.EXE @<<
      /B" /ALIGN:4 /EXEPACK /PACKCODE /PACKDATA /NOI /NOE /NOD /base:65536"
      /Fe"xlistbox.DLL" os2386.lib dde4mbsi.lib dde4cci.lib dde4muii.lib
      listbox.lib xlistbox.def
    $(OBJS)
<<
  implib xlistbox.LIB xlistbox.DLL

{.}.cpp.obj:
   ICC.EXE /Tl- /Tdp /O+ /Gm+ /Gd+ /Ge- /Ft- /C   .\$*.cpp

xlistbox.OBJ:  xlistbox.CPP xlistbox.HPP

xlisthdr.OBJ:  xlisthdr.CPP xlisthdr.HPP xlistbox.hpp xlistevt.hpp

xlistevt.OBJ:  xlistevt.CPP xlistevt.HPP

xlistini.OBJ:  xlistini.CPP

