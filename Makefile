# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Performance compiler flags
OPTFLAGS ?= --std=c++17 -Wall -Werror -pedantic -O3 -Wno-sign-compare -Wno-comment

test: CircularBuffer_tests.exe
	./CircularBuffer_tests.exe

CircularBuffer_tests.exe: CircularBuffer_tests.cpp CircularBuffer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

performance.exe: performance.cpp CircularBuffer.hpp
	$(CXX) $(OPTFLAGS) $< -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump
