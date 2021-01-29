.PHONY: gdb

CXXFLAGS=-Wall -Werror

NAME=simple-compiler

all: compiler

run: compiler
	./$(NAME).exe input.c

compiler:
	g++ *.cpp -o $(NAME).exe

log: logging
	./$(NAME).exe

logging:
	g++ -g -D LOGGING *.cpp -o $(NAME).exe
	
gdb: 
	g++ -g *.cpp -o $(NAME).exe

clean:
	rm *.o *.exe
