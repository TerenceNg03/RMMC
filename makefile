export

CC = g++
CFLAG = -std=c++17 -Wall 
INCLUDE = -I$(shell pwd)/include
DEFINE = -Dregister
FLAGS = ${CFLAG} ${INCLUDE} ${DEFINE}

LD = ld
LFLAGS = -r

RM = -@rm -f

.PHONY: subdir all run debug release

release: all

debug: CFLAG += -g -DDEBUG=1
debug: all

all: main.o subdir 
	${CC} ${CFLAGS} main.o lex/lex.o -o rmmc.out

run: all
	./rmmc.out

test:
	echo 'No unit test available yet'

subdir:
	${MAKE} -C lex lex.o
	${MAKE} -C frontend frontend.o

main.o: main.cpp
	${CC} ${FLAGS} -c main.cpp

clean:
	${MAKE} -C lex clean
	${MAKE} -C frontend clean
	${RM} *.o
	${RM} *.log
	${RM} rmmc.out
