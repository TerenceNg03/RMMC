.PHONY: clean

ast.o : ast_node.o compile2c.o
	${LD} ${LFLAGS} ast_node.o compile2c.o -o ast.o
	mkdir -p ${OBJ_PATH}
	cp ast.o ${OBJ_PATH}/
	
ast_node.o: ast_node.cc
	${CC} ${FLAGS} -c ast_node.cc

compile2c.o: compile2c.cc 
	${CC} ${FLAGS} -c compile2c.cc

clean:
	${RM} *.o
