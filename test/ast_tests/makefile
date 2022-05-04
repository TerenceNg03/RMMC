INCLUDE = -I $(shell pwd)/include

VPATH = src:include

.PHONY: run clean

run: test.out
	./test.out
test: test.cpp
	clang++ test.cpp ${INCLUDE} `llvm-config --cxxflags --ldflags --system-libs --libs core` -o test.out
clean: 
	${RM} *.o
	${RM} *.out
	${RM} *.log