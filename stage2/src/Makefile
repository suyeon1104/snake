CC = g++
#CPPFLAGS=-W -Wall -g -std=c++11
CPPFLAGS= -g -std=c++11
TARGET=snake
OBJECTS=snake.o

all:	$(TARGET)

$(TARGET):	$(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $^ -lncursesw
snake.o:	snake.cpp snake.h
	$(CC) $(CPPFLAGS) -c $<
clean:
	rm -rf *.o