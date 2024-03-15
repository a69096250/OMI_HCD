# ****************************************************************************
# *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
# *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
# *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
# *  included with this distribution for usage terms and conditions.
# ****************************************************************************
# *  File        : Makefile
# *  Date        : 2020-02-10
# *  Description : Unix makefile

EXE     = hostsim
SYSDIR  = ../..
OSNAME  = $(shell $(SYSDIR)/src/get_os -l)


ifdef 64BIT
ARCH    := $(addsuffix _64,$(OSNAME))
MKARGS  := 64BIT=1
else
ARCH    := $(OSNAME)
MKARGS  := 
endif

ifdef DEBUG 
LDOPT   := -g
ARCH    := $(ARCH)_dbg
MKARGS  := $(MKARGS) DEBUG=1
else 
LDOPT   := -O3 
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

ifeq (${OSNAME}, SUN)
  ifndef DEBUG
     LDOPT = -O
  endif

  ifdef 64BIT
  LDFLAGS := $(LDOPT) -xarch=v9 -dy -z text -Bsymbolic -KPIC -lm
  else
  LDFLAGS := $(LDOPT) -dy -z text -Bsymbolic -KPIC -lm
  endif
endif

ifeq (${OSNAME}, X86SUN)
  ifndef DEBUG
     LDOPT = -fast -xO3
  endif

  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -dy -z text -Bsymbolic -KPIC -lm
  else
  LDFLAGS := $(LDOPT) -m32 -dy -z text -Bsymbolic -KPIC -lm
  endif
endif



ifeq (${OSNAME}, RH)
  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -fpic -Wl,-Bsymbolic -lm
  else
  LDFLAGS := $(LDOPT) -m32 -fpic -Wl,-Bsymbolic -lm
  endif
endif

ifeq (${OSNAME}, SUSE)
  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -fpic -Wl,-Bsymbolic -lm
  else
  LDFLAGS := $(LDOPT) -m32 -fpic -Wl,-Bsymbolic -lm
  endif
endif



SRCS   = $(wildcard *.c) 

INCPATH = -I$(SYSDIR)/include -I$(SYSDIR)/models/common -I$(SYSDIR)/ut -I./
LIBPATH = $(SYSDIR)/lib/$(ARCH)
OBJPATH = $(SYSDIR)/obj/$(ARCH)
BINPATH = $(SYSDIR)/bin/$(ARCH)
OBJS    = $(addprefix $(OBJPATH)/, $(SRCS:.c=.o)) 
CCFLAGS = $(CCFLAG) $(INCPATH) 
TARGET  = $(BINPATH)/$(EXE) 
RMDIR   = rm -rf 
MKDIR   = mkdir -p 

define MKOBJPATH 
   if [ ! -d $(OBJPATH) ]; then $(MKDIR) $(OBJPATH); fi 
endef 

define MKBINPATH 
   if [ ! -d $(BINPATH) ]; then $(MKDIR) $(BINPATH); fi 
endef 

all: $(OBJS)
	@echo "making hostsim ..." 
	$(MKOBJPATH) 
	$(MKBINPATH) 
	$(CC) $(LDFLAGS) -L$(LIBPATH) -lOMImodel -o $(TARGET) $(OBJS)

$(OBJPATH)/%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

lint:
	lint $(INCPATH) $(SRCS) 


clean:
	@echo "cleaning hostsim ..."
	${RMDIR} $(OBJPATH) $(BINPATH)

