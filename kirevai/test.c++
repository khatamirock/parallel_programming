#include<iostream>
#include<stdio.h>
using namespace std;

template <typename T>
T adder(T a, T b){
    return a+b;
}


int kire(int &pp){
    cout<<"in kire\n";
    cout<<"*pp"<<"..\n\n\n\n\n"<<pp<<endl;
    return 0;
}


int main(){
    int n=10;
    int *p=&n;
    cout<<p<<" "<<*p<<endl;
    cout<<adder<float>(4.4,5.3);
    
    kire(*p);
}
