hello: hello_from_cpp.o hello_fun.o
	g++ -o hello hello_from_cpp.o hello_fun.o

hello_from_cpp.o: hello_from_cpp.c hello.hpp
	gcc -c hello_from_cpp.c

hello_fun.o:	hello_fun.cpp hello.hpp
	g++ -c hello_fun.cpp

run: hello
	./hello

clean:
	rm hello_from_cpp.o hello_fun.o hello
