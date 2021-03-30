.PHONY: gdb

CXXFLAGS=-Wall -Werror

NAME=simple-compiler

SOURCE= *.cpp nodes/*

all: compiler

run: compiler
	./$(NAME).exe sum.c

compiler:
	g++ $(SOURCE) -o $(NAME).exe

log: logging
	./$(NAME).exe	

logging:
	g++ -g -D LOGGING $(SOURCE) -o $(NAME).exe
	
debug: 
	g++ -g $(SOURCE) -o $(NAME).exe

clean:
	rm -f *.o *.exe

dry:
	echo $(SOURCE)
