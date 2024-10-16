# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

test: CircularBuffer_tests.exe
	./CircularBuffer_tests.exe

CircularBuffer_tests.exe: CircularBuffer_tests.cpp CircularBuffer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
performance.exe: performance.cpp CircularBuffer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump