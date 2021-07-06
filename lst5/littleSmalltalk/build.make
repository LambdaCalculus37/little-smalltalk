ARCH=`uname -s`
ARCHVERSION=`uname -r`
FULLARCH=$(ARCH)_$(ARCHVERSION)

CC=cc
#C=/usr/vacpp/bin/xlC
LIBS=
OBJS=main rss_dynload rss_queue memory interp ffi_primitives gui_primitives sqlite_primitives $(LST_OS_FILE)
OBJECTS=$(OBJS:=.o)

CFLAGS=-g -DLST_USE_GUI=0 -DLST_USE_FFI=1 -DLST_USE_SQLITE=0 -DARCH=$(ARCH) -DARCHVERSION=$(ARCHVERSION) -DFULLARCH=$(FULLARCH) -DLST_OS_HEADER=\"$(LST_OS_FILE).h\"


.SILENT:

.IGNORE:


default:		all

all:			welcome littleSmalltalk

.c.o:
			echo "Compiling $?..."
			$(CC) $(CFLAGS) -c $?

littleSmalltalk:	$(OBJECTS)
			$(CC) -o $@ $? $(LIBS)

clean:			
			rm -f *.o littleSmalltalk littleSmalltalk.static

welcome:
			echo
			echo "Compiling LittleSmalltalk on platform $(FULLARCH)..."
			echo "------------------------------------------------------------"

