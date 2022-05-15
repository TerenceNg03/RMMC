.PHONY: run clean
# CC = clang++
# CFLAG = -std=c++17 -Wall 
# INCLUDE = -I$(shell pwd)/../../include
# DEFINE = -Dregister
# FLAGS = ${CFLAG} ${INCLUDE} ${DEFINE}
# YFLAGS = -d -Wno-yacc
# OBJ_PATH = $(shell pwd)/../..//bin
# ROOT_DIR = $(shell pwd)/../../

run: test.out
	./test.out

test.out: test.o ${OBJ_PATH}/*.o
	${CC} ${FLAGS} ${GFLAGS} test.o ${OBJ_PATH}/*.o -o test.out ${GLFLAGS}

test.o: test.cc
	${CC} ${FLAGS} ${GFLAGS} `llvm-config --cxxflags --ldflags --system-libs --libs core` -c test.cc

clean: 
	${RM} *.o
	${RM} *.out
	${RM} *.log