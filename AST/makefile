.PHONY: clean
FLAGS += -I$(shell llvm-config --includedir) -I${ROOT_DIR}/lex

ast.o : AST.o xml.o
	${LD} ${LFLAGS} AST.o xml.o -o ast.o
	mkdir -p ${OBJ_PATH}
	cp ast.o ${OBJ_PATH}/

xml.o: xml.cc
	${CC} ${FLAGS} -c xml.cc

AST.o: AST.cc
	${CC} ${FLAGS} -c AST.cc

clean:
	${RM} *.o
