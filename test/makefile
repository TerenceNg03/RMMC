export
GFLAGS = -Igtest/include 
GLFLAGS = -lgtest -lpthread

.PHONY: all clean parser type

all: parser type

parser:
	${MAKE} -C parser_tests

type:
	${MAKE} -C type_tests

clean:
	${MAKE} -C parser_tests clean
	${MAKE} -C type_tests clean
