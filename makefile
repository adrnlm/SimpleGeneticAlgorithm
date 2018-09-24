all:
	gcc -ansi -pedantic -Wall *.c -o ga

debugmin:
	gcc -ansi -pedantic -Wall -D DEBUG *.c -o ga
	./ga minfn 4 20 10 minfnin.dat

debugpcb:
	gcc -ansi -pedantic -Wall -D DEBUG *.c -o ga
	./ga pcbmill 5 20 10 pcbin.dat

clean:
	rm ./ga*
