# ****************************************************************************
# *  Copyright (c) 2010 Taiwan Semiconductor Manufacturing Company, Ltd.
# *  Copyright (c) 2017-2021 Silicon Integration Initiative, Inc.
# *  See the file Si2_OMI_Licensed_Package_Statement_v1.0.txt
# *  included with this distribution for usage terms and conditions.
# ****************************************************************************
# *  File        : Makefile
# *  Date        : 2016-11-22
# *  Description : Unix makefile

LIB     = libOMImodel.so
SYSDIR  = ..
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

SRCDIR  = $(shell pwd)
DYN_LIB = ${LIB}.so

ifeq (${OSNAME}, SUN)
  ifndef DEBUG
     LDOPT = -O
  endif

  ifdef 64BIT
  LDFLAGS := $(LDOPT) -xarch=v9 -G -dy -z text -Bsymbolic -KPIC -lm
  else
  LDFLAGS := $(LDOPT) -G -dy -z text -Bsymbolic -KPIC -lm
  endif
endif

ifeq (${OSNAME}, X86SUN)
  ifndef DEBUG
     LDOPT = -fast -xO3
  endif

  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -G -dy -z text -Bsymbolic -KPIC -lm
  else
  LDFLAGS := $(LDOPT) -m32 -G -dy -z text -Bsymbolic -KPIC -lm
  endif
endif



ifeq (${OSNAME}, RH)
  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -fpic -shared -Wl,-Bsymbolic -lm
  else
  LDFLAGS := $(LDOPT) -m32 -fpic -shared -Wl,-Bsymbolic -lm
  endif
endif

ifeq (${OSNAME}, SUSE)
  ifdef 64BIT
  LDFLAGS := $(LDOPT) -m64 -fpic -shared -Wl,-Bsymbolic -lm
  else
  LDFLAGS := $(LDOPT) -m32 -fpic -shared -Wl,-Bsymbolic -lm
  endif
endif

LIBPATH = $(SYSDIR)/lib/$(ARCH)
OBJPATH = $(SYSDIR)/obj/$(ARCH)
TARGET  = $(LIBPATH)/$(LIB) 
RMDIR   = rm -rf 
MKDIR   = mkdir -p 

define MKOBJPATH 
   if [ ! -d $(OBJPATH) ]; then $(MKDIR) $(OBJPATH); fi 
endef 

define MKLIBPATH 
   if [ ! -d $(LIBPATH) ]; then $(MKDIR) $(LIBPATH); fi 
endef 

all:
	@echo "making OMI ..." 
	$(MKOBJPATH) 
	$(MKLIBPATH) 
	@cd ${SRCDIR}/simif; $(MAKE) ${MKARGS}; \
	cd ${SRCDIR}/ut   ; $(MAKE) ${MKARGS};
	@for subdir in `cat ${SRCDIR}/config`;\
	do cd ${SRCDIR}/$$subdir; $(MAKE) ${MKARGS};\
	done

	${CC} ${LDFLAGS} -o ${TARGET} ${OBJPATH}/*.o

lint:
	@echo "checking OMI ..."
	@cd ${SRCDIR}/simif; $(MAKE) lint;\
	cd ${SRCDIR}/ut    ; $(MAKE) lint;
	@for subdir in `cat ${SRCDIR}/config`;\
	do cd ${SRCDIR}/$$subdir; $(MAKE) lint;\
	done

clean:
	@echo "cleaning OMI ..."
	make -C simif clean
	make -C ut clean
	@for subdir in `cat ${SRCDIR}/config`;\
	do $(MAKE) -C $${subdir} clean; \
	done
	${RMDIR} $(OBJPATH) $(LIBPATH)
