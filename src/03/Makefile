include ../vars.mk
HEADERS = dyn_string.h
SRC = gearatio.c dyn_string.c
OBJS = gearatio.o dyn_string.o
DBGOBJS = dbggearatio.o dbgdyn_string.o

gearatio: $(SRC) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) -o $@.out $(OBJS)

debug: $(SRC) $(HEADERS) $(DBGOBJS)
	$(CC) $(DBGFLAGS) -o $@.out $(DBGOBJS)

gearatio.o: gearatio.c $(SRC) $(HEADERS)
dbggearatio.o: gearatio.c $(SRC) $(HEADERS)
	$(CC) $(DBGFLAGS) -o $@ -c $<

dyn_string.o: dyn_string.c $(SRC) $(HEADERS)
dbgdyn_string.o: dyn_string.c $(SRC) $(HEADERS)
	$(CC) $(DBGFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	if [ -f dbggearatio.o ]; \
		then rm $(DBGOBJS); \
	fi;
	if [ -f gearatio.o ]; \
		then rm $(OBJS); \
	fi;
