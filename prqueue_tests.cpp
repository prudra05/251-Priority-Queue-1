// Why the angle brackets? Grader reasons.
// Don't change this or you will be sad :(
#include <prqueue.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace std;
using namespace testing;

TEST(EmptyTest, Test) {
  prqueue<int> pq;
}

// Default constructor sets starting size incorrectly
TEST(PRQueueCore, DefaultSize) {
  prqueue<int> pq;

  int pqDefaultSize = pq.size();

  EXPECT_THAT(pqDefaultSize, Eq(0));
}

// Default construtor sets the root of tree incorrectly
TEST(PRQueueCore, DefaultRoot) {
  prqueue<string> pq;  // Is this ok?

  EXPECT_THAT(pq.getRoot(), Eq(nullptr));
}

// Size returns incorrect value
TEST(PRQueueCore, GetSize) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);

  int pqSize = pq.size();

  EXPECT_THAT(pqSize, Eq(3));
}

// clear resets size incorrectly
TEST(PRQueueCore, ClearSize) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);

  pq.clear();
  int pqSize = pq.size();

  EXPECT_THAT(pqSize, Eq(0));
}

TEST(PRQueueCore, EnqueueTest) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);
  string asStringExp = "4 value: Bernard\n5 value: Dolores\n8 value: Arnold\n";

  int pqSize = pq.size();
  string pqRoot = pq.getRoot()->value;
  string pqAsStr = pq.as_string();

  EXPECT_THAT(pqSize, Eq(3));
  EXPECT_THAT(pqRoot, Eq("Dolores"));
  EXPECT_THAT(pqAsStr, Eq(asStringExp));
}

// clear resets root incorrectly
TEST(PRQueueCore, ClearRoot) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);

  pq.clear();

  // prqueue<string> ab;

  EXPECT_THAT(pq.getRoot(), Eq(nullptr));
}


// improperly formatted + does not nclude all the elements of the prqueue in the
// returned string
TEST(PRQueueUsing, AsStringTest) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);
  string asStringExp = "4 value: Bernard\n5 value: Dolores\n8 value: Arnold\n";
  string pqAsStr = pq.as_string();

  EXPECT_THAT(pqAsStr, Eq(asStringExp));
}

// peek does not return return the correct value
TEST(PRQueueUsing, PeekTest) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);

  string peekVal = pq.peek();

  EXPECT_THAT(peekVal, Eq("Bernard"));
}

// dequeue does not return return the correct value + does not update size
TEST(PRQueueUsing, DequeValueNSize) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Dolores", 5);
  pq.enqueue("Bernard", 4);
  pq.enqueue("Arnold", 8);

  string dequeueVal = pq.dequeue();
  int pqSize = pq.size();

  EXPECT_THAT(dequeueVal, Eq("Bernard"));
  EXPECT_THAT(pqSize, Eq(2));
}

//Does not remove node from the tree + loses part of the tree when removed
TEST(PRQueueUsing, DequeRemove) {
  prqueue<string> pq;  // Is this ok?
  pq.enqueue("Sumayah", 10);
  pq.enqueue("Illyin", 8);
  pq.enqueue("Georgie", 9);
  pq.enqueue("Dylan", 7);
  pq.enqueue("Christyaan", 5);
  pq.enqueue("Gill", 6);
  string dequeueVal = pq.dequeue();
  string peekVal = pq.peek();

  EXPECT_THAT(dequeueVal, Eq("Christyaan"));
  EXPECT_THAT(peekVal, Eq("Gill"));
}
