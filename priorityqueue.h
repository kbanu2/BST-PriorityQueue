///@author Krenar Banushi
///@date April 11, 2023
///@brief This header provides the priorityqueue class and definitions.  A priorityqueue will store values in increasing order by priority. 
///       This implementation is templated to allow for any data type, but priorities must be integers.
///       Some main functions are enqueue, dequeue, begin, next, size, assignment operator, equality operator, toString
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

    /// @brief Return the second to last node in a list using a pointer to the head of the list
    /// @param head pointer to head of list
    /// @return pointer to second to last node in the list
    NODE* FindSecondToLast(NODE* head){
        NODE* current = head;
        while (current->link != nullptr){
            current = current->link;
        }
        return current;
    }

    /// @brief Append node to the end of a list and assign its parent to the head of the list
    /// @param head pointer to head of list
    /// @param nodeToInsert pointer of node to insert
    void PushBack(NODE* head, NODE* nodeToInsert){
        NODE* secondToLast = FindSecondToLast(head);

        secondToLast->link = nodeToInsert;
        nodeToInsert->parent = head;
        nodeToInsert->dup = true;
    }

    /// @brief Return leftmost node in the tree by traversing through node->left
    /// @param root pointer of node to begin search from
    /// @return pointer of left most node in the tree
    NODE* FindLeftMostNode(NODE* root){
        NODE* leftMost = root;
        while (leftMost->left != nullptr){
            leftMost = leftMost->left;
        }
        return leftMost;
    }

    /// @brief Recursively generate string of all node's priority and value followed by an endline 
    /// @param root pointer to the root of the binary search tree
    /// @return string of every node's priorities and values split by endlines
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

    /// @brief Recursively delete tree by starting from the bottom-up
    /// @param root pointer to root of tree
    void PostOrderDelete(NODE* root){
        if (root == nullptr)
            return;
        
        PostOrderDelete(root->left);
        PostOrderDelete(root->link);
        PostOrderDelete(root->right);

        delete root;
    }

    /// @brief Recursively deep copy tree into current tree using pointer to root of other tree
    /// @param root pointer to root of tree to copy
    void PreOrderCopy(NODE* root) {
        if (root == nullptr)
            return;

        this->enqueue(root->value, root->priority);
        PreOrderCopy(root->left);
        PreOrderCopy(root->link);
        PreOrderCopy(root->right);
    }
    
    /// @brief Remove node at the front of a duplicate list and reassign the parent node's left and right parameters to the next node in the list
    /// @param head pointer to head of the list
    void PopFront(NODE* head){
        if (head->parent == nullptr){
            root = head->link;

            root->parent = nullptr;
            root->dup = false;
            root->left = head->left;
            root->right = head->right;

            UpdateListParents(root);
        }
        else{
            NODE* next = head->link;

            head->parent->left = head->link;

            next->dup = false;
            next->parent = head->parent;
            next->left = head->left;
            next->right = head->right;

            UpdateListParents(next);
        }

        delete head;
    }

    /// @brief Update child nodes' parents to the provided pointer to the head of the list
    /// @param head pointer to set child nodes in list parent pointer to
    void UpdateListParents(NODE* head){
        NODE* current = head->link;

        while (current != nullptr){
            current->parent = head;
            current = current->link;
        }
    }

    /// @brief Delete root or subroot of the binary search tree and update parent pointer to next node
    /// @param subRoot pointer to root of tree to be deleted
    void DeleteSubRoot(NODE* subRoot){
        if (subRoot->parent == nullptr){
            root = subRoot->right;
            if (root != nullptr)
                root->parent = nullptr;
            delete subRoot;
            return;
        }
        
        if (subRoot->right != nullptr)
            subRoot->right->parent = subRoot->parent;
        subRoot->parent->left = subRoot->right;
        delete subRoot;
    }

    /// @brief return true if two binary search trees are equivalent to each other while also traversing duplicate nodes
    /// @param myRoot pointer to root of first tree to compare
    /// @param otherRoot pointer to root of second tree to compare
    /// @return true if the two trees are equivalent to each other, false otherwise
    bool PreOrderEquivalence(NODE* myRoot, NODE* otherRoot) const {
        if (myRoot == nullptr && otherRoot == nullptr)
            return true;
        else if (myRoot == nullptr || otherRoot == nullptr)
            return false;
        else{
            if (myRoot->priority == otherRoot->priority && myRoot->value == otherRoot->value && 
            PreOrderEquivalence(myRoot->left, otherRoot->left) && PreOrderEquivalence(myRoot->link, otherRoot->link) && PreOrderEquivalence(myRoot->right, otherRoot->right))
                return true;
            else
                return false;
        }
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
        temp->parent = nullptr;

        size++;
        if (root == nullptr){
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
                PushBack(current, temp);
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
        if (root == nullptr)
            return T{};
        
        NODE* current = FindLeftMostNode(root);
        T valueOut = current->value;

        if (current->link != nullptr)
            PopFront(current);
        else
            DeleteSubRoot(current);
        
        size--;
        return valueOut;
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
        curr = FindLeftMostNode(root);
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
        if (curr == nullptr)
            return false;

        value = curr->value;
        priority = curr->priority;

        if (curr->link != nullptr){
            curr = curr->link;
            return true;
        }
        
        if (curr->dup) //If down duplicate list
            curr = curr->parent; //Return to front of list
        
        if (curr->right != nullptr)
                curr = FindLeftMostNode(curr->right);
        else if (curr->parent != nullptr){
            //Traverse up parent nodes until the parent node is a left child
            while (curr->parent != nullptr && curr != curr->parent->left)
                curr = curr->parent;
            curr = curr->parent;
        }
        else
            curr = nullptr;

        if (curr == nullptr)
            return false;
        return true;
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
        if (root == nullptr)
            return T{};
        
        return FindLeftMostNode(root)->value;
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        return PreOrderEquivalence(root, other.root);
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
