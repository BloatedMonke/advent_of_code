include ../vars.mk

SRC = cube_conundrums.c
OBJS = cube_conundrums.o
DBGOBJS = dbgcube_conundrums.o
HEADERS =
.DEFAULT_GOAL = debug

include ../utils.mk

cube_conundrums: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(OBJS) $(COMMON_OBJS)
	$(CC) $(BUILD_FLAGS) -o $@.out $(OBJS) $(COMMON_OBJS)

debug: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(DBGOBJS) $(COMMON_DBGOBJS)
	$(CC) $(DBGFLAGS) -o $@.out $(DBGOBJS) $(COMMON_DBGOBJS)

cube_conundrums.o: cube_conundrums.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
dbgcube_conundrums.o: cube_conundrums.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
	$(CC) $(DBGFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm *.o
