#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;



template <class T> class Stack {

    struct element {
        T data;
        element* next;
    };


public:



    Stack(){
        top = nullptr;
        size = 0;


    };



    void push(T card) {

            element* holding = new element;
            holding->data = card;
            holding->next = top;
            top = holding;
            size++;

    }

    void pop() {
        element* temp = top;
        //cout << temp->data.name;
        top = temp->next;
        delete temp;
        size--;
    }

    T peek() {       
        if (isEmpty()) {
            //cout << "Stack is empty. There's nothing to see here!" << endl;
            return T();
        }

        else {
            return top->data;
        }
    }

    

    bool isEmpty() {
        if (top == nullptr) {
            //cout << "This stack is empty" << endl;
            return true;
        }

        else {
            //cout << "This stack has elements in it." << endl;
            return false;
        }
    }


    int checkSize() {
        //cout << endl << size<< endl;
        return size;  
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
    

private:
    element* top;
    int size;


};


#endif

