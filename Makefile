CFLAGS = -g -Wall
CC = gcc -lrt -lm

objects = cityVisit.o generation.o graph.o permut.o

test: $(objects)
	$(CC) -o cityVisit $(objects)

cityVisit.o: cityVisit.c graph.h permut.h generation.h
generation.o: generation.c generation.h permut.h graph.h
graph.o: graph.c graph.h
permut.o: permut.c permut.h graph.h

.PHONY : clean
clean:
	rm cityVisit $(objects)
