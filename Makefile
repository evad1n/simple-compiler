.PHONY: gdb

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

NAME=simple-compiler

SOURCE= *.cpp nodes/* machine-code/*

all: compiler

run: compiler
	./$(NAME).exe inputs/basic

compiler:
	g++ $(SOURCE) -o $(NAME).exe

machine: 
	g++-9 $(SOURCE) -o $(NAME).exe -z execstack
	./$(NAME).exe

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
