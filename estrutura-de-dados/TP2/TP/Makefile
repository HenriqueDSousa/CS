#     Makefile
#  
# Compila o arquivo main.cpp
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
OBJS = $(OBJ)/analisador.o $(OBJ)/palavra.o $(OBJ)/texto.o $(OBJ)/memlog.o
HDRS = $(INC)/palavra.h $(INC)/texto.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I $(INC)
ANALISAMEM = ../analisamem/bin/analisamem

ARQIN = entrada_1.txt
ARQOUT = output.txt
M = 3
S = 3

EXE = $(BIN)/analisador

all: mem perf gprof

#Analise de memoria -> gera arquivos .gp
mem: $(EXE)
	$(EXE) -i $(ARQIN) -m $(M) -s $(S) -o $(ARQOUT) -p /tmp/log.out -l 
	rm -rf /tmp/analisador
	mkdir /tmp/analisador
	$(ANALISAMEM) -i /tmp/log.out -p /tmp/analisador/analisador

#Analise de performance -> gera arquivos .out com o tempo de execucao
perf: $(EXE)
	rm -rf /tmp/perf
	mkdir /tmp/perf

	$(EXE) -i $(ARQIN) -m $(M) -s $(S) -o $(ARQOUT) -p /tmp/log.out
	

#Analise gprof -> gera arquivos .txt para depuracao
gprof: $(BIN)/analisador
	$(EXE) -i $(ARQIN) -m $(M) -s $(S) -o $(ARQOUT) -p /tmp/log.out
	gprof $(EXE) gmon.out > /tmp/gprof.txt

$(BIN)/analisador: $(OBJS)
	$(CC) -pg -o $(BIN)/analisador $(OBJS) $(LIBS)

$(OBJ)/analisador.o: $(HDRS) $(SRC)/analisador.cpp 
	$(CC) $(CFLAGS) -o $(OBJ)/analisador.o $(SRC)/analisador.cpp 

$(OBJ)/palavra.o: $(HDRS) $(SRC)/palavra.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/palavra.o $(SRC)/palavra.cpp

$(OBJ)/texto.o: $(HDRS) $(SRC)/texto.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/texto.o $(SRC)/texto.cpp

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 


	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
