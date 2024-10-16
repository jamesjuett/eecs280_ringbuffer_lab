// A program that compares a vector and CircularBuffer for implementing a
// qeueue.  The program will run a series of push and pop operations
// on both the vector and CircularBuffer and compare the time it takes to
// run through a million operations.

#include <iostream>
#include <vector>
#include <string>
#include "CircularBuffer.hpp"

using namespace std;


void test_vector(int N) {
  // Fill a vector with N integers
  vector<int> v;
  for (int i = 0; i < N; i++) {
    v.push_back(i);
  }

  // Push and pop N times
  for (int i = 0; i < N; i++) {
    v.push_back(i);
    
    // Vectors have no pop_front() function, but the
    // equivalent operation, v.erase(v.begin()) will remove
    // the first element and shift all the other elements down by one.
    v.erase(v.begin());
  }
}

// same as above but use a CircularBuffer instead of a vector
void test_circularbuffer(int N) {
  CircularBuffer<int> rb;

  // Fill a CircularBuffer with N integers
  for (int i = 0; i < N; i++) {
    rb.push_back(i);
  }

  // Push and pop N times
  for (int i = 0; i < N; i++) {
    rb.push_back(i);
    rb.pop_front();
  }
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
    cout << "Usage: ./performance.exe [container_type] [N]" << endl;
    return 1;
  }

  string container_type = argv[1];
  if(container_type != "vector" && container_type != "circularbuffer") {
    cout << "Error: container type must be \"vector\" or \"circularbuffer\"" << endl;
    return 1;
  }

  int N = stoi(argv[2]);

  if (container_type == "vector") {
    test_vector(N);
  } else {
    test_circularbuffer(N);
  }

}