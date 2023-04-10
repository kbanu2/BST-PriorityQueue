/// @filename tests.cpp
/// @author Krenar Banushi
/// @date April 11, 2023

/// Provided testing file to implement
/// framework based tests in using the GoogleTest framework

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

/// @brief Test if enqueue puts nodes in correct location for a balanced tree
///        Additionally uses Size, Begin, Next, toString 
TEST(priorityqueue, enqueue_balanced){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(0, 2);
    t.enqueue(1, 1);
    t.enqueue(5, 3);
    t.begin();

    t.toString();

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

/// @brief Test if enqueue works when inserting nodes to a subtree
///        Additionally uses Size, Begin, Next, toString 
TEST(priorityqueue, enqueue_subtree){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(5,5);
    t.enqueue(3,3);
    t.enqueue(4,4);
    t.enqueue(2,2);
    t.begin();

    t.toString();

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

/// @brief Test if dequeue will properly delete the leftmost node off the tree
///        Additionally uses enqueue, Size, Begin, Next, toString 
/// @param  
TEST(priorityqueue, dequeue_left){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(3,5);
    t.enqueue(1,2);
    t.enqueue(4,8);

    t.toString();

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

/// @brief Test to see if dequeue will properly delete the root and update it to null
///        Additionally uses enqueue, Size, Begin, Next, toString 
/// @param  
TEST(priorityqueue, dequeue_root){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(1,2);
    EXPECT_EQ(t.Size(), 1);
    EXPECT_EQ(t.dequeue(), 1);
    t.begin();
    EXPECT_EQ(t.next(val, pri), false);

    t.toString();
}

/// @brief Test if dequeue will properly delete root and reassign it with right child node
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

    t.toString();
}

/// @brief Test if dequeue can be used to properly delete entire priority queue
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

    t.toString();

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

    t.toString();
}

/// @brief Test if enqueue member function works with strings
///        Additionally uses Size, Begin, Next, toString
TEST(priorityqueue, enqueue_string){
    priorityqueue<string> t;
    string val;
    int pri;

    t.enqueue("t", 3);
    t.enqueue("e", 1);
    t.enqueue("h", 6);

    t.begin();
    EXPECT_EQ(t.Size(), 3);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, "e");
    EXPECT_EQ(pri, 1);
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, "t");
    EXPECT_EQ(pri, 3);
    EXPECT_EQ(t.next(val, pri), false);
    EXPECT_EQ(val, "h");
    EXPECT_EQ(pri, 6);

    t.toString();
}

/// @brief Test if the dequeue member function returns the correct type and correct value
///        Additionally uses enqueue, toString
TEST(priorityqueue, dequeue_char){
    priorityqueue<char> t;

    t.enqueue('c', 4);
    t.enqueue('d', 1);
    t.enqueue('h', 8);

    t.toString();
    EXPECT_EQ(t.dequeue(), 'd');
    EXPECT_EQ(t.dequeue(), 'c');
    EXPECT_EQ(t.dequeue(), 'h');
    t.toString();
}

/// @brief Test if next member function works to inorder traverse with double type
///        Additionally uses enqueue, Begin, toString
TEST(priorityqueue, next_double){
    priorityqueue<double> t;
    double val;
    int pri;

    t.enqueue(3.1, 1);
    t.enqueue(0, 6);
    t.enqueue(11.43, 0);

    t.toString();
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 11.43);
    EXPECT_EQ(pri, 0);
    EXPECT_EQ(t.next(val,pri), true);
    EXPECT_EQ(val, 3.1);
    EXPECT_EQ(pri, 1);
    EXPECT_EQ(t.next(val, pri), false);
    EXPECT_EQ(val, 0);
    EXPECT_EQ(pri, 6);
}

/// @brief Test if assignment operator will make a deep copy of given priorityqueue 
///        Additionally uses emqueue, dequeue, Size, Begin, Next, toString 
/// @param  
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

    h.toString();
    t.toString();
}

/// @brief Test to check if equality operator will propery return true when comparing two equivalent priorityqueues
///        Additionally uses enqeue Size, Begin, Next, toString 
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

    h.toString();
    t.toString();
}

/// @brief Test if equality operator will properly return false if there is an additional duplicate element in one of the queues
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

/// @brief Test if equality operator will return false if an additional node is added to one of the priority queues
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

    t.toString();
    h.toString();

    EXPECT_EQ((t == h), false);
}

/// @brief Test to see if equality operator will work if the conditions are flipped
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

    t.toString();
    h.toString();

    EXPECT_EQ((t == h), true);
    EXPECT_EQ((h == t), true);
}

/// @brief Test to see if next member function will return false on an empty priority queue
///        Additionally uses Size, Begin, Next, toString 
TEST(priorityqueue, next_empty){
    priorityqueue<int> t;
    int val, pri;

    t.begin();
    EXPECT_EQ(t.next(val, pri), false);
}

/// @brief Test to see if next member function will properly inorder traverse through priority queue
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

/// @brief Test to see if next member function works to traverse priority queue with duplicate entries
///        Additionally uses enqueue, Size, Begin, Next, toString 
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

/// @brief Test if peek member function returns value of node at front of queue
///        Additionally uses enqueue, dequeue
TEST(priorityqueue, peek){
    priorityqueue<int> t;

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

    EXPECT_EQ(t.peek(), 1);
    t.dequeue();
    EXPECT_EQ(t.peek(), 2);
    t.dequeue();
    EXPECT_EQ(t.peek(), 3);
    t.dequeue();
    EXPECT_EQ(t.peek(), 3);
}

/// @brief Test if the begin function will return the first node in the priorityqueue
///        Additionally uses enqueue, Next
TEST(priorityqueue, begin){
    priorityqueue<int> t;
    int val, pri;

    t.enqueue(4,3);
    t.enqueue(1,1);
    t.begin();
    EXPECT_EQ(t.next(val, pri), true);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(pri, 1);
    t.dequeue();
    t.begin();
    EXPECT_EQ(t.next(val, pri), false);
    EXPECT_EQ(val, 4);
    EXPECT_EQ(pri, 3);
}
