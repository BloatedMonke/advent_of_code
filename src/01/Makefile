include ../vars.mk
HEADERS = dyn_string.h
SRC = trebuchet.c dyn_string.c
OBJS = trebuchet.o dyn_string.o

trebuchet: $(OBJS) $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@.out $(OBJS) 

trebuchet.o: trebuchet.c $(HEADERS) $(SRC)
dyn_string.o: dyn_string.c $(HEADERS)

.PHONY: clean
clean:
	-rm *.o
