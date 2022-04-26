.PHONY: clean

frontend.o : rmm_types.o
	${LD} ${LFLAGS} rmm_types.o -o frontend.o
	mkdir -p ${OBJ_PATH}
	cp frontend.o ${OBJ_PATH}/

rmm_types.o: rmm_types.cc
	${CC} ${FLAGS} -c rmm_types.cc

clean:
	${RM} *.o
