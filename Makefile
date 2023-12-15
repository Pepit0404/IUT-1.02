testOffre: test.o offre.o
	gcc -Wall test.o offre.o -o test

offre.o: Offre/offre.c Offre/offre.h
	gcc -Wall -c Offre/offre.c

test.o: Offre/test.c Offre/offre.h
	gcc -Wall -c Offre/test.c

clean:
	rm *o test exe