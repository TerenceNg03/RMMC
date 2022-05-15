.PHONY: clean
FLAGS += -I$(shell llvm-config --includedir) -I${ROOT_DIR}/lex

gen.o: codegen.o
	${LD} ${LFLAGS} codegen.o -o gen.o
	mkdir -p ${OBJ_PATH}
	cp gen.o ${OBJ_PATH}/

codegen.o: codegen.cc
	${CC} ${FLAGS} -c codegen.cc

clean:
	${RM} *.o
