.PHONY: gdb

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

NAME=simple-compiler

SOURCE= *.cpp nodes/* machine-code/*

INPUT=inputs/scope.c

all: compiler

run: compiler
	./$(NAME).exe -i $(INPUT)

compiler:
	g++ $(SOURCE) -o $(NAME).exe

machine: 
	g++-9 $(SOURCE) -o $(NAME).exe -z execstack
	./$(NAME).exe $(INPUT)

log: logging
	./$(NAME).exe	

logging:
	g++ -g -D LOGGING $(SOURCE) -o $(NAME).exe
	
debug: 
	g++ -g $(SOURCE) -o $(NAME).exe

clean:
	rm -f *.o *.exe *.out

dry:
	echo $(SOURCE)
