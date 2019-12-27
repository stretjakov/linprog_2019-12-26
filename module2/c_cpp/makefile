.PHONY: clean all run
PROG_NAME = hello

all: $(PROG_NAME)

$(PROG_NAME): hello_from_cpp.o hello_fun.o
	g++ -o $(PROG_NAME) hello_from_cpp.o hello_fun.o

hello_from_cpp.o: hello_from_cpp.c hello.hpp

hello_fun.o:	hello_fun.cpp hello.hpp

run: $(PROG_NAME)
	./$(PROG_NAME)

clean:
	rm hello_from_cpp.o hello_fun.o $(PROG_NAME)
