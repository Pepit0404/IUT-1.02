exe: offre.o main.o
	gcc -Wall offre.o main.o -o exe

main.o: main.c
	gcc -Wall -c main.c

testOffre: test.o offre.o
	gcc -Wall testO.o offre.o -o testO

offre.o: Offre/offre.c Offre/offre.h
	gcc -Wall -g  -c Offre/offre.c

test.o: Offre/test.c Offre/offre.h
	gcc -Wall -g -c Offre/test.c

clean:
	rm *o testO testT exe