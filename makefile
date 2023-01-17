all: graph graph.o queue.o graph.c graph.h node.o

graph: graph.o queue.o node.o
	gcc -Wall -g -o graph graph.o queue.o node.o

node.o: node.c node.h
	gcc -Wall -g -c node.c

graph.o: graph.c graph.h
	gcc -Wall -g -c graph.c

queue.o: queue.c queue.h
	gcc -Wall -g -c queue.c
clean:
	rm graph *.o
