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
    EXPECT_EQ(t.next(val, pri), false);
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
    EXPECT_EQ(t.next(val, pri), false);
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
    EXPECT_EQ(t.next(val, pri), false);
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

TEST(priorityqueue, dequeue_entire){
    priorityqueue<int> t;

    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(4,10);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);
    t.enqueue(4,10);

    EXPECT_EQ(t.Size(), 10);
    EXPECT_EQ(t.dequeue(), 3);
    EXPECT_EQ(t.dequeue(), 1);
    EXPECT_EQ(t.dequeue(), 5);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 4);
    EXPECT_EQ(t.dequeue(), 8);
    EXPECT_EQ(t.dequeue(), 0);
    EXPECT_EQ(t.dequeue(), 10);
    EXPECT_EQ(t.dequeue(), 9);
}

TEST(priorityqueue, assignment){
    priorityqueue<int> t;
    priorityqueue<int> h;
    int valT, priT, valH, priH;

    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    h.begin();
    t.begin();
    EXPECT_EQ(t.Size(), h.Size());
    EXPECT_EQ((t == h), true);
    while(t.next(valT, priT) && h.next(valH, priH)){
        EXPECT_EQ(valT, valH);
        EXPECT_EQ(priT, priH);
    }

    while (h.Size() > 0){
        h.dequeue();
    }
    
    EXPECT_EQ(t.Size(), 8);
    t.begin();
    EXPECT_EQ(t.next(valT, priT), true);
    EXPECT_EQ(valT, 3);
    EXPECT_EQ(priT, 3);
}

TEST(priorityqueue, equality_equal){
    priorityqueue<int> t;
    priorityqueue<int> h;
    int val1, pri1, val2, pri2;

    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    EXPECT_EQ(t.Size(), h.Size());
    EXPECT_EQ((t == h), true);
    while (t.next(val1, pri1) && h.next(val2, pri2)){
        EXPECT_EQ(val1, val2);
        EXPECT_EQ(pri1, pri2);
    }
}

TEST(priorityqueue, equality_notequal_duplicate){
    priorityqueue<int> t;
    priorityqueue<int> h;

    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    h.enqueue(1,5);

    EXPECT_EQ(t.Size(), 12);
    EXPECT_EQ(h.Size(), 13);

    EXPECT_EQ((t == h), false);
}

TEST(priorityqueue, equality_notequal_leaf){
    priorityqueue<int> t;
    priorityqueue<int> h;

    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    t.enqueue(8,25);

    EXPECT_EQ(t.Size(), 13);
    EXPECT_EQ(h.Size(), 12);

    EXPECT_EQ((t == h), false);
}

TEST(priorityqueue, equality_reversed){
    priorityqueue<int> t;
    priorityqueue<int> h;

    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(4,10);
    t.enqueue(1,5);
    t.enqueue(3,3);
    t.enqueue(5,7);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(10,15);
    t.enqueue(8,12);
    t.enqueue(9,20);
    t.enqueue(0, 13);

    h = t;

    EXPECT_EQ((t == h), true);
    EXPECT_EQ((h == t), true);
}

TEST(priorityqueue, next_empty){
    priorityqueue<int> t;
    int val, pri;

    t.begin();
    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, next_nonempty_noduplicates){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(4,4);
    t.enqueue(2,2);
    t.enqueue(1,1);
    t.enqueue(3,3);
    t.enqueue(6,6);
    t.enqueue(5,5);
    t.enqueue(7,7);
    t.enqueue(8,8);
    t.begin();
    for (int i = 1; i < 8; i++){
        EXPECT_EQ(t.next(val, pri), true);
        EXPECT_EQ(val, i);
        EXPECT_EQ(pri, i);
    }
    EXPECT_EQ(t.next(val, pri), false);
    EXPECT_EQ(val, 8);
    EXPECT_EQ(pri, 8);

    EXPECT_EQ(t.next(val, pri), false);
}

TEST(priorityqueue, next){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(5,5);
    t.enqueue(3,3);
    t.enqueue(3,3);
    t.enqueue(1,1);
    t.enqueue(2,2);
    t.enqueue(2,2);
    t.enqueue(8,8);
    t.enqueue(5,5);
    t.enqueue(6,6);
    t.enqueue(6,6);
    t.enqueue(10,10);
    t.enqueue(10,10);

    t.begin();

    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(pri, 1);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 2);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 2);
    EXPECT_EQ(pri, 2);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 3);
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 5);
    EXPECT_EQ(pri, 5);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 6);
    EXPECT_EQ(pri, 6);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 6);
    EXPECT_EQ(pri, 6);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 8);
    EXPECT_EQ(pri, 8);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 10);
    EXPECT_EQ(pri, 10);
    EXPECT_EQ(t.next(val, pri), false);
    EXPECT_EQ(val, 10);
    EXPECT_EQ(pri, 10);
    EXPECT_EQ(t.next(val, pri), false);   
}
