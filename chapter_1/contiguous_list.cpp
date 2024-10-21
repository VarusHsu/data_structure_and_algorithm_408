#include<iostream>
#include "contiguous_list.h"
using namespace std;

template <typename T>
Contiguous<T>::Contiguous(){
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
    this->header = new T[INITIAL_CAPACITY];
}

template <typename T>
Contiguous<T>::~Contiguous(){

}

template <typename T>
bool Contiguous<T>::is_empty(){
    return this->size == 0;
}

template <typename T>
T* Contiguous<T>::pop_back(){
    if (this->size == 0 ){
        return nullptr;
    }
    return &this->header[--this->size];
}

template <typename T>
void Contiguous<T>::clear(){
    while(this->size>0){
        this->pop_back();
    }
    return;
}

template <typename T>
void Contiguous<T>::push_back(T value){
    if (this->capacity==this->size){
        this->grow();
    }
    this->header[this->size++] = value;
}


template <typename T>
void Contiguous<T>::grow(){
    if (this->capacity == 0) {
        this->capacity = 10;
    }else if (this->capacity <=256) {
        this->capacity *= 2;        
    }else {
        this->capacity = (this->capacity + 3 * THRESHOLD) >>2;
    }
    T* new_header = new T[this->capacity];
    for (int i =0; i < this->length(); i ++){
        new_header[i] = this-> header[i];
    }
    delete this->header;
    this-> header = new_header;
}

template<typename T>
int Contiguous<T>::length(){
    return this->size;
}

template<typename T>
T* Contiguous<T>::index_at(int index){
    if (index >= this->size){
        return nullptr;
    }

    return &this->header[index];
}

template<typename T>
void Contiguous<T>::print(){
    if (this->size == 0) {
        cout << "[]"<< endl;
    } else {
        cout<<"[";
        for (int i=0; i < this-> size; i++){
            cout<<*(this->index_at(i));
            if (i != this->size-1){
                cout<< " ";
                cout<< ",";
            }else {
                cout<< "]"<<endl;
            }
        }
    }

    cout<< "The length of contiguous is "<<this->size<<";"<<endl;
    cout<< "The capacity of contiguous is "<<this->capacity<<";"<<endl;
}


int main(){
    Contiguous<int> c;
    for (int i = 0; i < 300; i ++) {
        c.push_back(i);
        c.print();
    }

    c.clear();
    c.print();
}
