/// @file priorityqueue.h
///
///
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    NODE* FindSecondToLast(NODE* head){
        NODE* current = head;
        while (current->link != nullptr){
            current = current->link;
        }
        return current;
    }

    void PushBack(NODE* head, NODE* prev, NODE* nodeToInsert){
        if (head->link == nullptr){
            head->dup = true;
            head->link = nodeToInsert;
            nodeToInsert->parent = prev;
            return;
        }
        NODE* secondToLast = FindSecondToLast(head->link);
        secondToLast->link = nodeToInsert;
        nodeToInsert->parent = prev;
    }

    string InorderPrint(NODE* root){
        stringstream ss;
        string line;
        string temp;

        if (root == nullptr){
            return std::string();
        }

        line += InorderPrint(root->left);

        ss << root->priority << " " << root->value;
        ss >> temp;
        line += temp;
        line += " value: ";
        ss >> temp;
        line += temp;
        line += "\n";

        line += InorderPrint(root->link);
        line += InorderPrint(root->right);

        return line;
    }

    void PostOrderDelete(NODE* root){
        if (root == nullptr)
            return;
        
        PostOrderDelete(root->left);
        PostOrderDelete(root->link);
        PostOrderDelete(root->right);

        delete root;
    }

    void PreOrderCopy(NODE* root) {
        if (root == nullptr)
            return;

        this->enqueue(root->value, root->priority);
        PreOrderCopy(root->left);
        PreOrderCopy(root->link);
        PreOrderCopy(root->right);
    }

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        curr = nullptr;
        size = 0;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        this->clear();
        
        PreOrderCopy(other.root);

        return *this;
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        PostOrderDelete(root);
        root = nullptr;
        curr = nullptr;
        size = 0;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        clear();
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* temp = new NODE;
        temp->left = nullptr;
        temp->right = nullptr;
        temp->dup = false;
        temp->link = nullptr;
        temp->value = value;
        temp->priority = priority;

        size++;
        if (root == nullptr){
            temp->parent = nullptr;
            root = temp;
            return;
        }

        NODE* current = root;
        NODE* prev = nullptr;
        while (current != nullptr){
            if (priority < current->priority){ //Traverse left
                prev = current;
                current = current->left;
            }
            else if (priority > current->priority){ //Traverse right
                prev = current;
                current = current->right;
            }
            else{ //Duplicate
                current->dup = true;
                PushBack(current, prev, temp);
                return;
            }
        }

        if (prev->priority < temp->priority)
            prev->right = temp;
        else{
            prev->left = temp;
        }
        temp->parent = prev;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T dequeue() {
        NODE* current = root;
        T valueOut;

        while (current->left != nullptr){
            current = current->left;
        }

        if (current == root){ //Removing root, CAN contain duplicate

        }

        
        return valueOut; // TO DO: update this return
        
        
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        if (root == nullptr)
            return;

        curr = root;
        while (curr->left != nullptr){
            curr = curr->left;
        }
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
       return false;
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        return InorderPrint(root);
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
        
        
        // TO DO: write this function.
        T valueOut;
        return valueOut; // TO DO: update this return
        
        
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        
        
        // TO DO: write this function.
        return true; // TO DO: update this return
        
        
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
