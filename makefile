export

CC = g++
CFLAG = -std=c++17 -Wall 
INCLUDE = -I$(shell pwd)/include
DEFINE = -Dregister
FLAGS = ${CFLAG} ${INCLUDE} ${DEFINE}
YFLAGS = -d -Wno-yacc
OBJ_PATH = $(shell pwd)/bin
ROOT_DIR = $(shell pwd)

LD = ld
LFLAGS = -r

RM = -@rm -f

.PHONY: subdir all run debug release test test-parser

release: all

debug: CFLAG += -g -DDEBUG=1
debug: YFLAGS += -Wcex
debug: all

all: main.o subdir
	${CC} ${CFLAGS} main.o ${OBJ_PATH}/*.o -o rmmc.out

run: all
	./rmmc.out

test: all
	${MAKE} -C test
	
test-type: all
	${MAKE} -C test type

test-parser: all
	${MAKE} -C test parser

test-SDT: all
	${MAKE} -C test SDT

subdir:
	${MAKE} -C lex lex.o
	${MAKE} -C frontend frontend.o

main.o: main.cpp
	${CC} ${FLAGS} -c main.cpp

clean:
	${MAKE} -C lex clean
	${MAKE} -C frontend clean
	${MAKE} -C test clean
	${RM} *.o
	${RM} *.log
	${RM} *.xml
	${RM} rmmc.out
	${RM} -r bin/
