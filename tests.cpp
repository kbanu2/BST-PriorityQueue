#include <gtest/gtest.h>
#include <iostream>
#include "priorityqueue.h"
using namespace std;

/// @brief Test if the constructor initializes datamembers properly to 0
///        Additionally uses Size, Begin, Next, toString
/// @param  
TEST(priorityqueue, constructor){
    priorityqueue<int> t;
    int val, pri;

    t.begin();
    EXPECT_EQ(t.Size(), 0);
    EXPECT_EQ(t.next(val, pri), false);
    t.toString();
}

TEST(priorityqueue, enqueue_balanced){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(0, 2);
    t.enqueue(1, 1);
    t.enqueue(5, 3);
    t.begin();

    EXPECT_EQ(t.Size(), 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(pri, 1);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 0);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, enqueue_subtree){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(5,5);
    t.enqueue(3,3);
    t.enqueue(4,4);
    t.enqueue(2,2);
    t.begin();

    EXPECT_EQ(t.Size(), 4);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 2);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 4);
    EXPECT_EQ(pri, 4);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_left){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(3,5);
    t.enqueue(1,2);
    t.enqueue(4,8);
    

    EXPECT_EQ(t.Size(), 3);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.Size(), 2);
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 4);
    EXPECT_EQ(pri, 8);
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_root){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(1,2);
    EXPECT_EQ(t.Size(), 1);
    EXPECT_EQ(t.dequeue(), 1);
    t.begin();
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, dequeue_root_additional){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(1,2);
    t.enqueue(4,8);
    t.enqueue(3,5);
    t.enqueue(8,10);

    EXPECT_EQ(t.Size(), 4);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.Size(), 3);
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 5);
}