CC = gcc
DEBUG = -DDEBUG -g
CFLAGS = -ansi -pedantic -Wall
PROG = ga
OBJS = drive.o gene.o invector.o pop.o

all:
	$(CC) $(CFLAGS) *.c -o $(PROG)
	./$(PROG)

debug:
	$(CC) $(DEBUG) -o $(PROG) *.c
	./$(PROG)	

clean:
	rm -f *.o *.h.gch $(PROG)
