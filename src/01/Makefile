include ../vars.mk
SRC = trebuchet.c dyn_string.c
OBJS = trebuchet.o dyn_string.o
DBGOBJS = dbgtrebuchet.o dbgdyn_string.o
HEADERS =
.DEFAULT_GOAL = trebuchet

include ../utils.mk

trebuchet: $(OBJS) $(SRC) $(HEADERS)
	$(CC) $(BUILD_FLAGS) -o $@.out $(OBJS)

dbgtrebuchet:
	$(CC) $(CFLAGS) -o $@.out $(DBGOBJS)

trebuchet.o: trebuchet.c $(HEADERS) $(SRC)

dbgtrebuchet.o: trebuchet.c $(HEADERS) $(SRC)
	$(CC) $(DBGFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm *.o
