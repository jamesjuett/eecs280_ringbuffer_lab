# Compiler
CXX ?= g++

# Compiler flags
CXXFLAGS ?= --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

test: RingBuffer_tests.exe
	./RingBuffer_tests.exe

RingBuffer_tests.exe: RingBuffer_tests.cpp RingBuffer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@
	
performance.exe: performance.cpp RingBuffer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

.SUFFIXES:

.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump