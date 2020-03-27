all: basic_interpreter

basic_interpreter: main.cpp interpreter.o command.o boolean.o arithmetic.o
	g++ -g -Wall -std=c++11 main.cpp interpreter.o command.o boolean.o arithmetic.o -o basic_interpreter

interpreter.o: interpreter/interpreter.h interpreter/interpreter.cpp
	g++ -g -Wall -c -std=c++11 interpreter/interpreter.cpp -o interpreter.o

command.o: interpreter/command.h interpreter/command.cpp
	g++ -g -Wall -c -std=c++11 interpreter/command.cpp -o command.o

boolean.o: interpreter/boolean.h interpreter/boolean.cpp
	g++ -g -Wall -c -std=c++11 interpreter/boolean.cpp -o boolean.o

arithmetic.o: interpreter/arithmetic.h interpreter/arithmetic.cpp
	g++ -g -Wall -c -std=c++11 interpreter/arithmetic.cpp -o arithmetic.o