SHELL = /bin/sh
GCC = /usr/bin/gcc
CFLAGS= -D$(GXT_DEBUG) -Wall -fmax-errors=5

# Install paths according to GNU make standards
prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
includedir = $(prefix)/include
#TODO make the object directory a config choice
objdir = ~/Code/Obj

all: $(objdir)/libgxtnc.a
$(objdir)/libgxtnc.a: $(objdir)/nc_input.o $(objdir)/nc_menu.o $(objdir)/nc_message.o $(objdir)/nc_start.o \
			$(objdir)/nc_stop.o
	ar rs $(objdir)/libgxtnc.a $(objdir)/nc_*.o
$(objdir)/nc_input.o: nc_input.c
	$(GCC) $(CFLAGS) -c $^ -o $@
$(objdir)/nc_menu.o: nc_menu.c
	$(GCC) $(CFLAGS) -c $^ -o $@
$(objdir)/nc_message.o: nc_message.c
	$(GCC) $(CFLAGS) -c $^ -o $@
$(objdir)/nc_start.o: nc_start.c
	$(GCC) $(CFLAGS) -c $^ -o $@
$(objdir)/nc_stop.o: nc_stop.c
	$(GCC) $(CFLAGS) -c $^ -o $@

clean:
	@rm *~

install: $(includedir)/nc_main.h
$(includedir)/nc_main.h: nc_main.h
	sudo cp $^ $@

uninstall:
	sudo rm $(includedir)/nc_main.h
