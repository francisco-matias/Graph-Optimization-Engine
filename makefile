CC = gcc 

TARGET = wrdmttns

CFLAGS = -Wall -std=c99 -O3

all:
		$(CC) $(CFLAGS) -o $(TARGET) main.c fase2.c Djikstra.c fase1.c

clear:
		rm $(TARGET)