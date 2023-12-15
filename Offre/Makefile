test: test.o offre.o
	gcc -Wall test.o offre.o -o test

offre.o: offre.c offre.h
	gcc -Wall -c offre.c

test.o: test.c offre.h
	gcc -Wall -c test.c

clean:
	rm *.o test