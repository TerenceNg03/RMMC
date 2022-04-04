.PHONY: run clean

run: test.o
	${CC} ${FLAGS} ${GFLAGS} test.o ${OBJ_PATH}/*.o -o test.out ${GLFLAGS}
	./test.out

test.o: test.cc
	${CC} ${FLAGS} ${GFLAGS} -c test.cc

clean: 
	${RM} *.o
	${RM} *.out
	
