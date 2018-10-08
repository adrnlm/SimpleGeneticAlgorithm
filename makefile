CC = gcc
DEBUG = -DDEBUG -g -lm
CFLAGS = -ansi -pedantic -Wall -lm
PROG = ga
OBJS = drive.o gene.o invector.o pop.o

all: $(OBJS)
	$(CC) $(CFLAGS) *.c -o $(PROG)

debug:
	$(CC) $(DEBUG) -o $(PROG) *.c

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

run:
	./$(PROG)

clean:
	rm -f *.o *.h.gch $(PROG)
