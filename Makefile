# generated automatically by encore, date 2011-07-22 14:24:36.185198

CPU=L865
KVER=2.6.24.7-rt27
KERNELSRC=/acc/sys/$(CPU)/usr/src/kernels/$(KVER)
include /acc/dsc/src/co/Make.auto

DRIVER = ctc
DRIVER_NAME = "$(DRIVER)"
LIBNAME = lib$(DRIVER)
USERLIB = lib$(DRIVER)user

COMPILE_TIME = $(shell date +%s)
GIT_VERSION = $(shell git describe --dirty --tags --all --long)
CFLAGS= -g -Wall -I. -I ../../driver
CFLAGS += -I /acc/local/$(CPU)/include/
CFLAGS += -DCOMPILE_TIME=$(COMPILE_TIME) -g -Wall -fPIC

MODLIBS = $(LIBNAME).$(CPU).a $(LIBNAME).$(CPU).so \
	$(USERLIB).$(CPU).a $(USERLIB).$(CPU).so
MODLIBOBJS = $(LIBNAME).$(CPU).o $(DRIVER)_regs.$(CPU).o
USERLIBOBJS = $(USERLIB).$(CPU).o libencore.$(CPU).a
ENCORELIBS = libencore.$(CPU).a libencore.$(CPU).so
DOCDIR = ./doc

SRCS=$(LIBNAME).c $(LIBNAME).h

all: modules libs docs
libs: $(MODLIBS) $(ENCORELIBS)
modules:
	cp Module.symvers.vmebus Module.symvers
	make -C $(KERNELSRC) M=`pwd` GIT_VERSION=$(GIT_VERSION) 'DRIVER_NAME=$(DRIVER_NAME)' modules
clean:
	make -C $(KERNELSRC) M=$(PWD) clean
	rm -f *.o *.a *.so
	rm -rf default.doxycfg doc

$(LIBNAME).$(CPU).o: $(SRCS)

$(LIBNAME).$(CPU).a: $(MODLIBOBJS)
	$(AR) $(ARFLAGS) $@ $^

$(USERLIB).$(CPU).o: libctcuser.c libctcuser.h
$(USERLIB).$(CPU).a: $(USERLIBOBJS)
	$(AR) $(ARFLAGS) $@ $^
$(USERLIB).$(CPU).so: $(USERLIBOBJS)
	$(CC) $(CFLAGS) -o $@ -shared $^

lib$(DRIVER).$(CPU).so: lib$(DRIVER).$(CPU).o
	$(CC) -shared -o $@ $^

libencore.$(CPU).o: libencore.c libencore.h
libencore.$(CPU).a: libencore.$(CPU).o
	$(AR) $(ARFLAGS) $@ $^
libencore.$(CPU).so: libencore.$(CPU).o
	$(CC) $(CFLAGS) -o $@ -shared $^

default.doxycfg:
	sh makedox.sh

docs:	default.doxycfg
	mkdir -p $(DOCDIR)
	sh doxy.sh -o $(DOCDIR) -nlibctcuser  libctcuser.h
scp -r doc/html/* cs-ccr-www3:/var/www/html/private/coht/doxy/ctc
