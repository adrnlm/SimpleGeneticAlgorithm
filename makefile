CC = gcc
DEBUG = -DDEBUG -g
CFLAGS = -ansi -pedantic -Wall
PROG = ga
OBJS = drive.o gene.o invector.o pop.o

all: $(OBJS)
	$(CC) $(CFLAGS) *.c -o $(PROG) -lm

val: $(OBJS)
	$(CC) $(CFLAGS) -g *.c -o $(PROG) -lm

debug:
	$(CC) $(DEBUG) -o $(PROG) *.c -lm

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o *.h.gch $(PROG)
