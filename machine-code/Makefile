.PHONY: gdb

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

NAME=machine-code

all: build

run: build
	./$(NAME).exe

run2: build2
	./$(NAME).exe

build:
	g++ *.cpp -o $(NAME).exe 
	execstack -s $(NAME).exe 

build2:
	g++ *.cpp -o $(NAME).exe -z execstack
	
debug: 
	g++ -g *.cpp -o $(NAME).exe

clean:
	rm -f *.o *.out* *.exe*

one:
	g++ -c main.cpp  -fno-stack-protector -D_FORTIFY_SOURCE=0

docker-gcc:
	docker run -it --name simple-compiler --mount type=bind,source="$(shell pwd)",target=/app simplecompiler:latest

docker-ubuntu:
	docker run -it --name simple-compiler-ubuntu --mount type=bind,source="$(shell pwd)",target=/app simplecompiler-ubuntu:latest

# To allow executing compiled code in the data segment from Linux Ubuntu:

# Putty to your Linux machine (oxygen or nitrogen) as an admin user, and type: 
# $ sudo apt-get install execstack

# Then as yourself,
# 	compile each source file with these extra options:
# $ g++ -c main.cpp  -fno-stack-protector -D_FORTIFY_SOURCE=0
# 	etc.
# Link.

# Then:
#  $ execstack -s ./a.out

# Then:
#  $./a.out
