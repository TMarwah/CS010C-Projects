#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 20;
template <typename T>
class stack{

    private:
        T data[MAX_SIZE];
        unsigned int size;
    
    public:
        stack()
        : size(0){}

        void push(T val){
            try{
                if(size+1 > MAX_SIZE){
                    throw overflow_error("Push called on full stack");
                }
                else{
                    data[size] = val;
                    size += 1;
                }
            }
            catch(const std::overflow_error& excpt){
            cout << excpt.what() << endl;
            }
        }

        void pop(){
            try{
                if(size == 0){
                    throw out_of_range("Called pop on empty stack");
                }
                else{
                    data[size-1] = 0;
                    size -= 1;
                }
            }
            catch
        }

        void pop_two(){
            try{
                if(size == 0){
                    throw out_of_range("Called pop_two on empty stack");
                }
                else if(size == 1){
                    throw out_of_range("Called pop_two on stack of size 1");
                }
                else{
                    data[size-1] = 0;
                    data[size-2] = 0;
                    size -= 2;
                }
            }
            catch(const std::out_of_range& excpt){
            cout << excpt.what() << endl;
            }
        }
        //return top value of stack
        T top(){
            return data[size-1];

        }

        //check if stack is empty through size var
        bool empty(){
            if(size == 0){
                return true;
            }
            else{
                return false;
            }
        }
};
