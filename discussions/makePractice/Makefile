cxx = g++
OBJS = adder.o math.o
DEPS = math.h
TARGET = adder

all: adder

adder: adder.o math.o
	$(CXX) -o adder adder.o math.o

adder.o: adder.cpp math.h
	$(CXX) -o adder.o -c adder.cpp

math.o: math.cpp math.h
	$(CXX) -O math.o

clean
