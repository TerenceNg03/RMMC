.PHONY: run clean

run: test.out
	./test.out --gtest_output=xml:${ROOT_DIR}/SDT.xml

test.out: test.o ${OBJ_PATH}/*.o
	${CC} ${FLAGS} ${GFLAGS} test.o ${OBJ_PATH}/*.o -o test.out ${GLFLAGS}

test.o: test.cc
	${CC} ${FLAGS} ${GFLAGS} -c test.cc

clean: 
	${RM} *.o
	${RM} *.out
	${RM} *.log
	
