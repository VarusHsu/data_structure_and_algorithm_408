#include<iostream>
#include "contiguous_list.h"
using namespace std;

template <typename T>
Contiguous<T>::Contiguous(){
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
}

int main(){
    Contiguous<int> c;
    cout<<"Hello"<<endl;
    return 0;
}