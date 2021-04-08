.PHONY: gdb

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

NAME=machine-code

all: build

run: build
	./$(NAME).exe

build:
	g++ *.cpp -o $(NAME).exe -z execstack
	
debug: 
	g++ -g *.cpp -o $(NAME).exe

clean:
	rm -f *.o *.out* *.exe*

one:
	g++ -c main.cpp  -fno-stack-protector -D_FORTIFY_SOURCE=0

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
