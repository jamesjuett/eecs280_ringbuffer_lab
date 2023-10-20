// A program that compares a vector and RingBuffer for implementing a
// qeueue.  The program will run a series of push and pop operations
// on both the vector and RingBuffer and compare the time it takes to
// run through a million operations.

#include <iostream>
#include <vector>
#include <string>
#include "RingBuffer.hpp"

using namespace std;


void test_vector() {
  // Fill a vector with 100,000 integers
  vector<int> v;
  for (int i = 0; i < 100000; i++) {
    v.push_back(i);
  }

  // Push and pop a million times
  for (int i = 0; i < 1000000; i++) {
    v.push_back(i);
    
    // Vectors have no pop_front() function, but the
    // equivalent operation, v.erase(v.begin()) will remove
    // the first element and shift all the other elements down by one.
    v.erase(v.begin());
  }
}

// same as above but use a RingBuffer instead of a vector
void test_ringbuffer() {
  RingBuffer<int> rb;

  // Fill a RingBuffer with 100,000 integers
  for (int i = 0; i < 100000; i++) {
    rb.push_back(i);
  }

  // Push and pop a million times
  for (int i = 0; i < 1000000; i++) {
    rb.push_back(i);
    rb.pop_front();
  }
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Usage: ./performance.exe [container_type]" << endl;
    return 1;
  }

  string container_type = argv[1];
  if(container_type != "vector" && container_type != "ringbuffer") {
    cout << "Error: container type must be \"vector\" or \"ringbuffer\"" << endl;
    return 1;
  }

  if (container_type == "vector") {
    test_vector();
  } else {
    test_ringbuffer();
  }

}