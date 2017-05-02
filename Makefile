CC = clang
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3

all: muttype.h main

muttype.h: muttype.gperf
	gperf -t muttype.gperf > muttype.h

main: main.o

test:
	@chmod +x one_run
	@./one_run main

clean:
	@rm -f main main.o *.db *.csv muttype.h

.PHONY: test clean all
