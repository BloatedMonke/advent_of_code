VPATH = ../../include ../../dyn_string
CC = gcc
INCLUDES = -I../../include
CFLAGS = $(INCLUDES) -Wall -Wpedantic -Wextra
DBGFLAGS = $(CFLAGS) -g3 -O0
SANITIZE = -fsanitize=address
DBGFLAGS += $(SANITIZE)
 