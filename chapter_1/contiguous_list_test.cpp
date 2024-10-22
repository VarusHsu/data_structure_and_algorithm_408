#include "contiguous_list.h"
#include<iostream>

int main(){
    std::cout<<"hello"<<std::endl;    
}

void test_contiguous_list_is_empty(){
    Contiguous<int> c;

    
}

bool assert_equals_int(int val1, int val2){
    if (val1 == val2) {
        return true;
    }
    std::cerr<<"assert failed: " << val1 << " is not equals to " << val2<<std::endl; 
    exit(1);
}