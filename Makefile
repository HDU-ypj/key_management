CC=gcc
BIN=project
OBJ=main.o tools.o function.o list.o 
FLAG=-Wall-Werror-DDEBUG
STD=-std=gnu99

all:$(OBJ)
	$(CC) -o $(BIN) $(OBJ) && ./$(BIN)

main.o:main.c function.h
	gcc -c main.c -o main.o 
tools.o:tools.c tools.h function.h list.h
	gcc -c tools.c -o tools.o
function.o:function.c function.h list.h tools.h
	gcc -c function.c -o function.o
list.o:list.c list.h
	gcc -c list.c -o list.o

clean:
	rm $(BIN) $(OBJ) 
