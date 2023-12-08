include ../vars.mk

SRC = scratchcards.c
OBJS = scratchcards.o
DBGOBJS = dbgscratchcards.o
HEADERS =
.DEFAULT_GOAL = scratchcards

include ../utils.mk

scratchcards: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(OBJS) $(COMMON_OBJS)
	$(CC) $(BUILD_FLAGS) -o $@.out $(OBJS) $(COMMON_OBJS)

debug: $(SRC) $(HEADERS) $(COMMON_HEADERS) $(DBGOBJS) $(COMMON_DBGOBJS)
	$(CC) $(DBGFLAGS) -o $@.out $(DBGOBJS) $(COMMON_DBGOBJS)

scratchcards.o: scratchcards.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
dbgscratchcards.o: scratchcards.c $(SRC) $(HEADERS) $(COMMON_HEADERS)
	$(CC) $(DBGFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm *.o
