include ../vars.mk
HEADERS = dyn_string.h
SRC = trebuchet.c dyn_string.c
OBJS = trebuchet.o dyn_string.o
DBGOBJS = dbgtrebuchet.o dbgdyn_string.o

trebuchet: $(OBJS) $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@.out $(OBJS)

dbgtrebuchet:
	$(CC) $(CFLAGS) -o $@.out $(DBGOBJS)

trebuchet.o: trebuchet.c $(HEADERS) $(SRC)
dyn_string.o: dyn_string.c $(HEADERS)

dbgtrebuchet.o: trebuchet.c $(HEADERS) $(SRC)
	$(CC) $(DBGFLAGS) -o $@ $<

dbgdyn_string.o: dyn_string.c $(HEADERS)
	$(CC) $(DBGFLAGS) -o $@ $<

.PHONY: clean
clean:
	-rm *.o
