export
GFLAGS = -Igtest/include 
GLFLAGS = -lgtest -lpthread

.PHONY: all clean parser 

all: parser

parser:
	${MAKE} -C parser_tests

clean:
	${MAKE} -C parser_tests clean
