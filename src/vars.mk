path_to_my_dir := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
VPATH = $(path_to_my_dir)common $(path_to_my_dir)common/dyn_string
CC = gcc
INCLUDES = -I$(path_to_my_dir)common -I$(path_to_my_dir)common/dyn_string/
CFLAGS = $(INCLUDES) -Wall -Wpedantic -Wextra
BUILD_FLAGS = -Wall -Wpedantic -Wextra
DBGFLAGS = $(CFLAGS) -g3 -O0
SANITIZE = -fsanitize=address -fsanitize=undefined
DBGFLAGS += $(SANITIZE)
