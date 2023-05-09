#     Makefile
#  
# Compila o arquivo server.cpp
#
# Opcoes: make all- compila tudo
#				make mem - gera arquivos de registro de acesso
#               make perf - faz medidas de tempo de desempenho
#               make gprof - ilustra uso do gprof para depuração
#		  make clean - remove objetos e executável
#


CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/server.o $(OBJ)/bst.o $(OBJ)/hash.o $(OBJ)/mensage.o $(OBJ)/memlog.o
HDRS = $(INC)/bst.h $(INC)/hash.h $(INC)/mensage.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I $(INC)
ANALISAMEM = ../analisamem/bin/analisamem

ARQIN = input.txt
ARQOUT = output.txt

EXE = $(BIN)/server

all: mem perf gprof

#Analise de memoria -> gera arquivos .gp
mem: $(EXE)
	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out -l 
	rm -rf /tmp/server
	mkdir /tmp/server
	$(ANALISAMEM) -i /tmp/log.out -p /tmp/server/server

#Analise de performance -> gera arquivos .out com o tempo de execucao
perf: $(EXE)
	rm -rf /tmp/perf
	mkdir /tmp/perf

	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out -l
	

#Analise gprof -> gera arquivos .txt para depuracao
gprof: $(BIN)/server
	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out -l
	gprof $(EXE) gmon.out > /tmp/gprof.txt

$(BIN)/server: $(OBJS)
	$(CC) -pg -o $(BIN)/server $(OBJS) $(LIBS)

$(OBJ)/server.o: $(HDRS) $(SRC)/server.cpp 
	$(CC) $(CFLAGS) -o $(OBJ)/server.o $(SRC)/server.cpp 

$(OBJ)/bst.o: $(HDRS) $(SRC)/bst.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/bst.o $(SRC)/bst.cpp

$(OBJ)/hash.o: $(HDRS) $(SRC)/hash.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/hash.o $(SRC)/hash.cpp

$(OBJ)/mensage.o: $(HDRS) $(SRC)/mensage.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/mensage.o $(SRC)/mensage.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 


	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
