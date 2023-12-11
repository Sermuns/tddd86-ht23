//
// Created by Thicc on 2023-12-05.
//

#include <iostream>
#include "MyVector.h"

using namespace std;
int main(){
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);

    cout << v[0] << endl;
    cout << v[1] << endl;

    cout << "Sizes" << endl;
    cout << v.size() << endl;
    v.pop_back();
    cout << v.size() << endl;

    cout << "Clear" << endl;
    cout << v[0] << endl;
    cout << v[1] << endl;
    return 0;
}