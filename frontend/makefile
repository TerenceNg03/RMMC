.PHONY: clean

frontend.o : rmm_types.o rmm_utility.o
	${LD} ${LFLAGS} rmm_types.o rmm_utility.o -o frontend.o
	mkdir -p ${OBJ_PATH}
	cp frontend.o ${OBJ_PATH}/

rmm_types.o: rmm_types.cc
	${CC} ${FLAGS} -c rmm_types.cc

rmm_utility.o: rmm_utility.cc
	${CC} ${FLAGS} -c rmm_utility.cc

clean:
	${RM} *.o
