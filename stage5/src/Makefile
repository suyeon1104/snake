CC = g++
#CPPFLAGS=-W -Wall -g -std=c++11
CPPFLAGS= -g -std=c++11
TARGET=main
OBJECTS=main.o map.o snake.o

all:	clean $(TARGET)
UNAME_S := $(shell uname -s)

$(TARGET):	$(OBJECTS)
ifeq ($(UNAME_S),Darwin)
	# Since mac os does not support ncursesw, so it must not delete.
	$(CC) $(CPPFLAGS) -o $@ $^ -lncurses
else
	# for only linux
	$(CC) $(CPPFLAGS) -o $@ $^ -lncursesw
endif
snake.o:	snake.cpp snake.h
	$(CC) $(CPPFLAGS) -c $<
map.o:	map.cpp map.h
	$(CC) $(CPPFLAGS) -c $<
clean:
	rm -rf *.o $(TARGET)
