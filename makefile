CC = gcc
FLAGS = -g -Wall

all : Main


Main : Main.o StrList.o
	$(CC) $(FLAGS) Main.o StrList.o -o Main

Main.o : Main.c StrList.h
	$(CC) $(FLAGS) -c Main.c

StrList.o : StrList.c StrList.h
	$(CC) $(FLAGS) -c StrList.c




clean : 
	rm Main  *.o