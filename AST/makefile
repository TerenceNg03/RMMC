.PHONY: clean

ast.o : ast_node.o
	${LD} ${LFLAGS} ast_node.o -o ast.o
	mkdir -p ${OBJ_PATH}
	cp ast.o ${OBJ_PATH}/
	
ast_node.o: ast_node.cc
	${CC} ${FLAGS} -c ast_node.cc

clean:
	${RM} *.o
