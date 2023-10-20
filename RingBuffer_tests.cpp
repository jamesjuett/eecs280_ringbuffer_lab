#include <iostream>
#include <sstream>
#include <string>

#include "unit_test_framework.hpp"
#include "RingBuffer.hpp"

using namespace std;

TEST(ringbuffer_default_constructor) {
  RingBuffer<int> rb;
  ASSERT_TRUE(rb.empty());
  ASSERT_EQUAL(rb.size(), 0);
}

TEST(ringbuffer_push_pop) {
  RingBuffer<int> rb;
  rb.push_back(5);
  ASSERT_EQUAL(rb.size(), 1);
  ASSERT_EQUAL(rb.front(), 5);

  rb.push_back(10);
  ASSERT_EQUAL(rb.size(), 2);
  ASSERT_EQUAL(rb.front(), 5);

  rb.push_back(15);
  ASSERT_EQUAL(rb.size(), 3);
  ASSERT_EQUAL(rb.front(), 5);

  rb.pop_front();
  ASSERT_EQUAL(rb.size(), 2);
  ASSERT_EQUAL(rb.front(), 10);

  rb.pop_front();
  ASSERT_EQUAL(rb.size(), 1);
  ASSERT_EQUAL(rb.front(), 15);

  rb.pop_front();
  ASSERT_EQUAL(rb.size(), 0);
  ASSERT_TRUE(rb.empty());

  rb.push_back(20);
  ASSERT_EQUAL(rb.size(), 1);
  ASSERT_EQUAL(rb.front(), 20);

  rb.pop_front();
  ASSERT_EQUAL(rb.size(), 0);
  ASSERT_TRUE(rb.empty());
}

TEST(ringbuffer_at) {
  RingBuffer<int> rb;
  rb.push_back(5);
  rb.push_back(10);
  rb.push_back(15);
  ASSERT_EQUAL(rb.at(0), 5);
  ASSERT_EQUAL(rb.at(1), 10);
  ASSERT_EQUAL(rb.at(2), 15);

  const RingBuffer<int> &const_rb = rb;
  ASSERT_EQUAL(const_rb.at(0), 5);
  ASSERT_EQUAL(const_rb.at(1), 10);
  ASSERT_EQUAL(const_rb.at(2), 15);

  rb.pop_front();
  ASSERT_EQUAL(rb.at(0), 10);
  ASSERT_EQUAL(rb.at(1), 15);
  ASSERT_EQUAL(const_rb.at(0), 10);
  ASSERT_EQUAL(const_rb.at(1), 15);
}

// Tests for copy constructor
TEST(ringbuffer_copy_constructor) {
  RingBuffer<int> rb;
  rb.push_back(5);
  rb.push_back(10);
  rb.push_back(15);
  
  RingBuffer<int> rb2(rb);
  ASSERT_EQUAL(rb2.at(0), 5);
  ASSERT_EQUAL(rb2.at(1), 10);
  ASSERT_EQUAL(rb2.at(2), 15);
  ASSERT_EQUAL(rb2.size(), 3);

  // Make a change to rb2
  rb2.pop_front();
  ASSERT_EQUAL(rb2.at(0), 10);
  ASSERT_EQUAL(rb2.at(1), 15);
  ASSERT_EQUAL(rb2.size(), 2);

  // Make sure rb is not affected
  ASSERT_EQUAL(rb.at(0), 5);
  ASSERT_EQUAL(rb.at(1), 10);
  ASSERT_EQUAL(rb.at(2), 15);
  ASSERT_EQUAL(rb.size(), 3);
}

// Tests for assignment operator
// TEST(ringbuffer_assignment_operator) {
//   RingBuffer<int> rb;
//   rb.push_back(5);
//   rb.push_back(10);
//   rb.push_back(15);
  
//   RingBuffer<int> rb2;
//   rb2.push_back(20);
//   rb2.push_back(25);

//   // assign, overwriting rb2 and its old data
//   rb2 = rb;

//   ASSERT_EQUAL(rb2.at(0), 5);
//   ASSERT_EQUAL(rb2.at(1), 10);
//   ASSERT_EQUAL(rb2.at(2), 15);
//   ASSERT_EQUAL(rb2.size(), 3);

//   // Make a change to rb2
//   rb2.pop_front();
//   ASSERT_EQUAL(rb2.at(0), 10);
//   ASSERT_EQUAL(rb2.at(1), 15);
//   ASSERT_EQUAL(rb2.size(), 2);

//   // Make sure rb is not affected
//   ASSERT_EQUAL(rb.at(0), 5);
//   ASSERT_EQUAL(rb.at(1), 10);
//   ASSERT_EQUAL(rb.at(2), 15);
//   ASSERT_EQUAL(rb.size(), 3);
// }

// Tests for growing the ring buffer
TEST(ringbuffer_grow) {
  RingBuffer<int> rb;
  for (int i = 0; i < 4; ++i) { // initial capacity is 4
    rb.push_back(i);
  }
  ASSERT_EQUAL(rb.size(), 4);
  ASSERT_EQUAL(rb.at(3), 3);
  
  // This will trigger the grow function
  rb.push_back(10);
  ASSERT_EQUAL(rb.size(), 5);
  ASSERT_EQUAL(rb.at(0), 0);
  ASSERT_EQUAL(rb.at(1), 1);
  ASSERT_EQUAL(rb.at(2), 2);
  ASSERT_EQUAL(rb.at(3), 3);
  ASSERT_EQUAL(rb.at(4), 10);
}

// Tests for overloaded operator
TEST(ringbuffer_ostream_operator) {
  RingBuffer<int> rb;
  rb.push_back(5);
  rb.push_back(10);
  rb.push_back(15);
  rb.push_back(20);
  rb.pop_front();
  
  std::ostringstream oss;
  oss << rb;
  
  ASSERT_EQUAL(oss.str(), "[ 10, 15, 20 ]");
}

TEST_MAIN() // No semicolon!
