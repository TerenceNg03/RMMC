.PHONY: clean

lex.o: scanner.o parser.o driver.o scanner.o
	
	${LD} ${LFLAGS} scanner.o parser.o driver.o -o lex.o
	mkdir -p ${OBJ_PATH}
	cp lex.o ${OBJ_PATH}/
	

scanner.o: scanner.l scanner.hh parser.o

	${LEX} -o scanner.cc scanner.l
	${CC} ${FLAGS} -c scanner.cc -o scanner.o

parser.o: parser.y

	${YACC} -d -Wno-yacc parser.y -o parser.cc
	${CC} ${FLAGS} -c parser.cc -o parser.o

driver.o: driver.cc scanner.o parser.o

	${CC} ${FLAGS} -c driver.cc -o driver.o

clean:
	${RM} location.hh
	${RM} position.hh
	${RM} *.o
	${RM} parser.hh
	${RM} parser.cc
	${RM} scanner.cc
	${RM} stack.hh
