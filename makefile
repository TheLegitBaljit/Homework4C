all: graph graph.o queue.o graph.c graph.h edge.c edge.h node.o

graph: graph.o queue.o edge.o node.o
	gcc -Wall -g -o graph graph.o queue.o edge.o node.o

node.o: node.c node.h
	gcc -Wall -g -c node.c

edge.o: edge.c edge.h
	gcc -Wall -g -c edge.c

graph.o: graph.c graph.h
	gcc -Wall -g -c graph.c

queue.o: queue.c queue.h
	gcc -Wall -g -c queue.c
clean:
	rm graph *.o
