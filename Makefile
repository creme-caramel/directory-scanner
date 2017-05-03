CC = clang
CFLAGS = -g -c -Wall
LDFLAGS = -lsqlite3

all: muttype.h main

muttype.h: muttype.gperf
	gperf -t muttype.gperf > muttype.h

main: main.o

run:
	@chmod +x run
	@./run main

clean:
	@rm -f main main.o *.db *.csv muttype.h

.PHONY: run clean all
