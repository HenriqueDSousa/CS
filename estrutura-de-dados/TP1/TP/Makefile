#     Makefile
#  
# Compila o programa gameop
#
# Opcoes: make all- compila tudo
#				make mem - gera arquivos de registro de acesso
#               make perf - faz medidas de tempo de desempenho
#               make gprof - ilustra uso do gprof para depuração
#		  make clean - remove objetos e executável
#


CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/gameop.o $(OBJ)/carta.o $(OBJ)/jogador.o $(OBJ)/mesa.o $(OBJ)/memlog.o
HDRS = $(INC)/carta.h $(INC)/jogador.h $(INC)/mesa.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I $(INC)
ANALISAMEM = ../analisamem/bin/analisamem
ARQIN = entrada.txt
ARQOUT = saida.txt

EXE = $(BIN)/gameop

all: mem perf gprof

#Analise de memoria -> gera arquivos .gp
mem: $(EXE)
	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out -l 
	rm -rf /tmp/poker
	mkdir /tmp/poker
	$(ANALISAMEM) -i /tmp/log.out -p /tmp/poker/poker

#Analise de performance -> gera arquivos .out com o tempo de execucao
perf: $(EXE)
	rm -rf /tmp/perf
	mkdir /tmp/perf

	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out 

#Analise gprof -> gera arquivos .txt para depuracao
gprof: $(BIN)/gameop
	$(EXE) -i $(ARQIN) -o $(ARQOUT) -p /tmp/log.out 
	gprof $(EXE) gmon.out > /tmp/gprof.txt

$(BIN)/gameop: $(OBJS)
	$(CC) -pg -o $(BIN)/gameop $(OBJS) $(LIBS)

$(OBJ)/gameop.o: $(HDRS) $(SRC)/gameop.c
	$(CC) $(CFLAGS) -o $(OBJ)/gameop.o $(SRC)/gameop.c 

$(OBJ)/carta.o: $(HDRS) $(SRC)/carta.c
	$(CC) $(CFLAGS) -o $(OBJ)/carta.o $(SRC)/carta.c

$(OBJ)/jogador.o: $(HDRS) $(SRC)/jogador.c
	$(CC) $(CFLAGS) -o $(OBJ)/jogador.o $(SRC)/jogador.c

$(OBJ)/mesa.o: $(HDRS) $(SRC)/mesa.c
	$(CC) $(CFLAGS) -o $(OBJ)/mesa.o $(SRC)/mesa.c

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 


	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
