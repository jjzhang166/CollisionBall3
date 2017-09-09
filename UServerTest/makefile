.PHONY:clean
SRC=$(wildcard *.cpp)
CXX=g++
DEFINES= 
CFLAGS= -m64 -pipe -g -Wall -W -fPIC $(DEFINES)
CXXFLAGS=-g -std=c++14 -Wall -W -fPIC $(DEFINES)

main:$(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread -lunet 

clean:
	rm *.o  
