u_path_to_my_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

include $(u_path_to_my_dir)/vars.mk

dyn_string.o: dyn_string.c dyn_string.h
dbgdyn_string.o: dyn_string.c dyn_string.h
	$(CC) $(DBGFLAGS) -o $@ -c $<

utility.o: utility.c utility.h
dbgutility.o: utility.c utility.h
	$(CC) $(DBGFLAGS) -o $@ -c $<

COMMON_OBJS = dyn_string.o utility.o
COMMON_HEADERS = dyn_string.h utility.h
COMMON_DBGOBJS = dbgdyn_string.o dbgutility.o