.PHONY: clean
FLAGS += -I$(shell llvm-config --includedir) -I${ROOT_DIR}/lex

codegen.o: CodeGen.cc
	${CC} ${FLAGS} -c CodeGen.cc
	mkdir -p ${OBJ_PATH}
	cp ast.o ${OBJ_PATH}/

clean:
	${RM} *.o
