.PHONY: clean

frontend.o : rmm_types.o
	${LD} ${LFLAGS} rmm_types.o -o frontend.o

rmm_types.o: rmm_types.cc
	${CC} ${FLAGS} -c rmm_types.cc

clean:
	rm *.o
