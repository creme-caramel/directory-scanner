#FILEPATH := $(realpath $(lastword $(MAKEFILE_LIST)))
#CURDIR := $(shell cd $(dir $(FILEPATH));pwd)

CC = clang
CFLAGS = -g -c -Wall -pedantic -Wextra -Wno-unused-parameter
LDFLAGS = -lsqlite3
#LDFLAGS = -L$(CURDIR)/lib -lsqlite3
#RPATH = -Wl,-rpath=$(CURDIR)/lib
#INC = -I$(CURDIR)/inc

all: main

main: main.o

test:
	@chmod +x one_run
	@./one_run main

clean:
	@rm -f main main.o *.db *.csv

.PHONY: test clean all
