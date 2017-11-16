IN=tiotom.cpp
OUT=tiotom
CC=g++
FLAGS=-lm
TESTE=teste1.txt

all: PROJETO TEST

PROJETO: $(IN)
	$(CC) -o $(OUT) $(IN) $(FLAGS)

TEST: PROJETO
	./$(OUT) < $(TESTE)

.PHONY: all