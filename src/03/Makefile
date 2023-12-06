include ../vars.mk
SRC = gearatio.c dyn_string.c
OBJS = gearatio.o
DBGOBJS = dbggearatio.o
HEADERS =
.DEFAULT_GOAL = gearatio

include ../utils.mk

gearatio: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(OBJS) $(COMMON_OBJS)
	$(CC) $(BUILD_FLAGS) -o $@.out $(OBJS) $(COMMON_OBJS)

debug: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(DBGOBJS) $(COMMON_DBGOBJS)
	$(CC) $(DBGFLAGS) -o $@.out $(DBGOBJS) $(COMMON_DBGOBJS)

gearatio.o: gearatio.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
dbggearatio.o: gearatio.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
	$(CC) $(DBGFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm *.o
