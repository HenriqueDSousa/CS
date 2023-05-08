CC = g++
LIBS = -lm
OBJS = graph.o candidatura.o main.o
HDRS = graph.h candidatura.h 
SRC = main.cpp graph.cpp candidatura.cpp
CFLAGS = -pg -Wall

#compilando todo arq .cpp em arquivos .o

tp01: $(OBJS)
	$(CC) $(FLAGS) -o tp01 $(OBJS) $(LIBS)

graph.o: graph.cpp
	$(CC) $(CFLAGS) -c graph.cpp

candidatura.o: candidatura.cpp
	$(CC) $(CFLAGS) -c candidatura.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp




clean:
	rm -f *.o tp01