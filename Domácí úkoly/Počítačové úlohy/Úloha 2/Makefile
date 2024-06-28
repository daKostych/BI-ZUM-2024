CXX=g++
LD=g++
AR=ar
CXXFLAGS=-std=c++20 -Wall -pedantic -g

OBJS = main.o path.o tmatrix.o bruteforce.o genetic.o
TARGET = bi-zum-salesman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(CXXFLAGS) -o $@ $^
%.o: %.cpp    $(CXX) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -f *.o $(TARGET) *~ core sample.tgz Makefile.d
-include Makefile.d
bruteforce.o: bruteforce.cpp bruteforce.h tmatrix.h
path.hgenetic.o: genetic.cpp genetic.h tmatrix.h path.h
main.o: main.cpp tmatrix.h path.h bruteforce.h
genetic.hpath.o: path.cpp path.h tmatrix.h
tmatrix.o: tmatrix.cpp tmatrix.h
