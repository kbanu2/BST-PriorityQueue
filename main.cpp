#include <iostream>
#include "priorityqueue.h"
using namespace std;

int main(){
    priorityqueue<int> t;
    priorityqueue<int> h;
    int value, priority;
    //cout << t.Size();
    t.enqueue(4,1);
    t.enqueue(5,5);
    t.enqueue(8,4);
    t.enqueue(6,1);
    t.enqueue(0, 3);
    t.enqueue(-1,4);
    t.enqueue(0,11);
    t.enqueue(3, 0);
    t.enqueue(8, -1);
    t.enqueue(0, 0);

    //h = t;

    //cout << t.Size();
    cout << t.toString() << endl << endl;
    
    while (t.Size() > 0){
        cout << t.peek() << " ";
        cout << t.dequeue() << endl;
    }

    

    // t.begin();
    // int i = 0;
    // while (t.next(value, priority)){
    //     cout << priority << " value: " << value << endl;
    //     i++;
    // }

    t.clear();

    //cout << h.toString();
}

