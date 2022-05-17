.PHONY: clean
FLAGS += -I$(shell llvm-config --includedir) -I$(shell llvm-config --bindir) -I${ROOT_DIR}/lex

ast.o : _ast.o json.o
	${LD} ${LFLAGS} _ast.o json.o -o ast.o
	mkdir -p ${OBJ_PATH}
	cp ast.o ${OBJ_PATH}/

json.o: json.cc
	${CC} ${FLAGS} -c json.cc

_ast.o: AST.cc
	${CC} ${FLAGS} -c AST.cc -o _ast.o

clean:
	${RM} *.o
