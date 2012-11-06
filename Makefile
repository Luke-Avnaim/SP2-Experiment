CFLAGS=
CC=g++
TARGET=main

all:
	$(CC) main.cpp SP1.cpp SP2.cpp mask.cpp -o $(TARGET)
