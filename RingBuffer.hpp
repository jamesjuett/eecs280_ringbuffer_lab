#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <iostream>

template <typename T>
class RingBuffer {

public:

  // EFFECTS: Constructs an empty RingBuffer.
  RingBuffer()
    : data(new T[INITIAL_CAPACITY]),
    head(0), tail(0), num_elts(0), capacity(INITIAL_CAPACITY) {

  }
  
  RingBuffer(const RingBuffer<T> &other)
    : data(new T[other.capacity]),
      capacity(other.capacity) {
    
    copy_data_from(other);
  }
    
  // REQUIRES: buffer is not full
  // EFFECTS:  Adds a new value to the back of the buffer
  //           moves tail to the new position
  void push_back(const T &value) {
    // TODO: Write your implementation here
  }

  // REQUIRES: buffer is not empty
  // EFFECTS:  Removes the element at the front of the buffer
  //           moves head to the new position
  void pop_front() {
    // TODO: Write your implementation here
  }

  // REQUIRES: buffer is not empty
  // EFFECTS:  Returns the value at the front of the buffer
  T &front() {
    // TODO: Write your implementation here
  }

  // EFFECTS:  Returns the current size of the buffer
  int size() const{
    return num_elts;
  }

   // EFFECTS:  Returns true if this RingBuffer is empty, false otherwise.
  bool empty() const {
    return num_elts == 0;
  }

   // EFFECTS:  Returns true if this RingBuffer is at capacity, false otherwise.
  bool full() const {
    return num_elts == capacity;
  }

  // REQUIRES: 0 <= index and index < number of elements in this RingBuffer.
  // EFFECTS:  Returns (by reference) the element that is index positions from head.
  T & at(int index) {
    return data[(head + index) % capacity];
  }

  // REQUIRES: 0 <= index and index < number of elements in this RingBuffer.
  // EFFECTS:  Returns (by const reference) the element that is index positions from head.
  const T & at(int index) const {
    return data[(head + index) % capacity];
  }

  ~RingBuffer() {
    delete[] data;
  }

  // EFFECTS : prints the buffer to os 
  void print(std::ostream &os) const{
    os << "[ ";
    for (int i = 0; i < num_elts; ++i) {
        os << at(i);
        if (i < num_elts - 1) {
            os << ", ";
        }
    }
    os << " ]";
  }

private:

  // The capacity (maximum size) of an RingBuffer is 30 elements.
  static const int INITIAL_CAPACITY = 4;

  // The array to hold the N elements stored in this ring buffer in positions determined
  // by head and tail
  T * data;

  // head is the index marking the beginning of the data in the buffer
  // tail is the index where a new element would be added in the buffer
  // num_elts is the number of elements currently in the buffer
  int head;
  int tail;
  int num_elts;
  int capacity;

  void grow() {

    // Place elements at the start of a new, larger array
    T *new_data = new T[2*capacity];
    for(int i = 0; i < num_elts; ++i) {
      new_data[i] = at(i);
    }

    delete data;
    data = new_data;

    head = 0;
    tail = num_elts;
    capacity *= 2;
    // num_elts remains the same
  }

  // REQUIRES: destination points to the start of an array with length >= num_elts
  // EFFECTS:  Copies all elements from this ring buffer into the provided
  //           destination array. They are copied to beginning of the destination
  //           array (at positions 0...num_elts-1), regardless of where they are
  //           in the original internal data array.
  void copy_data_from(const RingBuffer &other) {

    // Copy elements from other, placing at the start of our own array
    for(int i = 0; i < other.num_elts; ++i) {
      // using .at(i) accounts for possibly different head/tail of other
      data[i] = other.at(i);
    }
    
    // Adjust head/tail and num_elts to match new data
    head = 0;
    tail = other.num_elts;
    num_elts = other.num_elts;
  }

};

// EFFECTS : overloaded operator that prints the buffer to os
template <typename T>
std::ostream& operator<<(std::ostream &os, const RingBuffer<T> &rb) {
    rb.print(os);
    return os;
}

#endif // Do not remove this. Write all your code above this line.
