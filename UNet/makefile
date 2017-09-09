.PHONY:clean
SRC=$(wildcard *.cpp *.h)
CC=g++
std=c++14 
CFLAGS=-Wall -shared -fPIC
DEFINES =
CXXFLAGS= -m64 -pipe -g -std=c++14 -Wall -W -shared -fPIC $(DEFINES)
TARGET=libunet.so

$(TARGET):$(SRC)
	$(CC) $(CXXFLAGS) $^ -o $@
