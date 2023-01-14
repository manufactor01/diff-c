CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --show-reachable=yes --track-origins=yes
FILE = diff.c
OBJFILE = diff.o 
EXEC = pruebas
%.o: %.c
	$(CC) $(CFLAGS) -c $<
$(EXEC): $(OBJFILE)
	$(CC) $(CFLAGS) $(OBJFILE) -o $(EXEC)

all: $(EXEC)
clear:
	clear
run1:
	./$(EXEC) nombres1.txt nombres2.txt
run2: 
	./$(EXEC) nombres1.txt nombres3.txt
run3:
	./$(EXEC) nombres2.txt nombres3.txt
run4:
	./$(EXEC) nombres1.txt nombres4.txt
free: $(EXEC) $(OBJFILE)
	rm -f $(EXEC) $(OBJFILE)

val1: all clear
	valgrind $(VFLAGS) ./pruebas nombres1.txt nombres2.txt
val2: all clear
	valgrind $(VFLAGS) ./pruebas nombres2.txt nombres3.txt
val3: all clear
	valgrind $(VFLAGS) ./pruebas nombres1.txt nombres3.txt
val4: all clear
	valgrind $(VFLAGS) ./pruebas nombres1.txt nombres4.txt