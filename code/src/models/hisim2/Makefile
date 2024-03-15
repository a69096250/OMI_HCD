# *************************************************
# *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
# *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
# *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
# *  included with this distribution for usage terms and conditions.
# *************************************************
# *  File        : Makefile
# *  Date        : 2010_1123
# *  Description : Unix makefile

SYSDIR  = ../..
OSNAME  = $(shell $(SYSDIR)/get_os -l)
MID     = HiSIM2
MABV    = HSM2

ifdef 64BIT
ARCH    := $(addsuffix _64,$(OSNAME))
MKARGS  := 64BIT=1
else
ARCH    := $(OSNAME)
MKARGS  :=
endif

ifdef DEBUG
CCOPT   := -g
ARCH    := $(ARCH)_dbg
MKARGS  := $(MKARGS) DEBUG=1
else
CCOPT   := -O3
ARCH    := $(ARCH)
MKARGS  := $(MKARGS)
endif

ifeq (${OSNAME}, SUN)
  ifndef DEBUG 
    CCOPT  = -xO3 -xtarget=ultra3 -fns -fsimple=1
  endif  
  ifdef 64BIT
  CCFLAG  := $(CCOPT) -xarch=v9 -KPIC
  else
  CCFLAG  := $(CCOPT) -KPIC 
  endif
endif

ifeq (${OSNAME}, X86SUN)
  ifndef DEBUG 
    CCOPT  = -fast -xO3 -fns -fsimple=1 -xtarget=pentium4
  endif  
  ifdef 64BIT
  CCFLAG  := $(CCOPT) -m64 -KPIC
  else
  CCFLAG  := $(CCOPT) -m32 -KPIC 
  endif
endif

ifeq (${OSNAME}, RH)
  ifdef 64BIT
  CCFLAG  := $(CCOPT) -m64 -msse2 -mfpmath=sse -fpic -shared
  else
  CCFLAG  := $(CCOPT) -m32 -msse2 -mfpmath=sse -fpic -shared
  endif
endif

ifeq (${OSNAME}, SUSE)
  ifdef 64BIT
  CCFLAG  := $(CCOPT) -m64 -msse2 -mfpmath=sse -fpic -shared
  else
  CCFLAG  := $(CCOPT) -m32 -msse2 -mfpmath=sse -fpic -shared
  endif
endif



GENSRCS = omi$(MID)BuildParam.c \
          omi$(MID)InitInstParam.c \
          omi$(MID)InitModelParam.c \
          omi$(MID)Set.c \
          omi$(MID)SetInstParam.c \
          omi$(MID)SetModelParam.c
SRCS   = $(wildcard *.c) $(GENSRCS)

INCPATH = -I$(SYSDIR)/../include -I$(SYSDIR)/models/common -I$(SYSDIR)/ut -I./
OBJPATH = $(SYSDIR)/../obj/$(ARCH)
OBJS    = $(addprefix $(OBJPATH)/, $(SRCS:.c=.o)) 
CCFLAGS = $(CCFLAG) $(INCPATH) 

RMDIR   = rm -rf 
MKDIR   = mkdir -p 

define MKOBJPATH 
   if [ ! -d $(OBJPATH) ]; then $(MKDIR) $(OBJPATH); fi 
endef 

compile: $(OBJS)
	
omi$(MID)Def.h $(GENSRCS): parameters
	python ../common/gen_param_code.py $(MID) $(MABV)

$(OBJPATH)/%.o:%.c omi$(MID)Def.h
	$(CC) $(CCFLAGS) -c $< -o $@ 

%.c:
	$(MKOBJPATH) 

clean:
	-rm -f omi$(MID)Def.h
	-rm -f omi$(MID)BuildParam.c
	-rm -f omi$(MID)InitInstParam.c
	-rm -f omi$(MID)InitModelParam.c
	-rm -f omi$(MID)Set.c
	-rm -f omi$(MID)SetInstParam.c
	-rm -f omi$(MID)SetModelParam.c
	-rm -f omi$(MID)Temp.inc
	$(RMDIR) $(OBJS) 


lint:
	lint $(INCPATH) $(SRCS) 

