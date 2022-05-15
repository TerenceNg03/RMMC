export
GFLAGS = -Igtest/include 
GLFLAGS = -lgtest -lpthread

.PHONY: all clean parser type

all: parser type SDT

parser:
	${MAKE} -C parser_tests

type:
	${MAKE} -C type_tests

SDT:
	${MAKE} -C SDT_tests

ast:
	${MAKE} -C ast_tests

clean:
	${MAKE} -C parser_tests clean
	${MAKE} -C type_tests clean
	${MAKE} -C SDT_tests clean
