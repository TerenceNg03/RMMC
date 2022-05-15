.PHONY: run clean
FLAGS += -I$(shell llvm-config --includedir) -I$(shell llvm-config --bindir) -I${ROOT_DIR}/lex

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