#include <iostream>
#include "MyVector.h"

template <class T>
void printVector(MyVector<T> vector)
{
    for (auto i = vector.begin(); i != vector.end(); ++i)
    {
        std::cout << *i << ' ';
    }
    std::cout << std::endl;
}

int main()
{
    // tests for Vector.cpp without iterators
    MyVector<int> vector;
    vector.push_back(1);
    vector.push_back(2);
    vector.push_back(3);
    printVector(vector);
    vector.pop_back();
    printVector(vector);
    vector.clear();
    int a[3] = {1, 4, 7};
    MyVector<int> vector2(a, 3);
    printVector(vector2);
    vector = vector2;
    vector2.clear();
    printVector(vector);
    vector.push_back(93);
    MyVector<int> vector3(vector);
    vector.clear();
    printVector(vector3);
    std::cout << vector3.at(2) << vector3.front() << vector3.back() << vector3[1] << std::endl;
    std::cout << (vector3 == vector3) << (vector3 == vector) << (vector != vector2) << std::endl;
    std::cout << vector3.size() << vector3.capacity() << vector.length() << vector.capacity() << std::endl;
    vector3.insert(2, 43);
    printVector(vector3);
    vector3.erase(1, 3);
    printVector(vector3);
    vector3.erase(0);
    printVector(vector3);
    vector.insert(0, a, 3);
    vector3.insert(0, vector);
    printVector(vector3);
    vector.insert(2, 555, 8);
    printVector(vector);
    vector[2] = 1;
    vector.at(4) = 77;
    printVector(vector);
    vector.erase(0, 213133);
    printVector(vector);
    std::cout << vector.capacity() << '\n';
    // tests for iterators
    std::cout << *vector3.begin() << '\n';
    std::cout << *(vector3.begin()++) << '\n';
    std::cout << *(--vector3.end()) << '\n';
    printVector(vector);
    std::cout << '\n';
    vector.insert(0, vector3.begin(), vector3(3));
    printVector(vector);
    auto iterator = vector.begin();
    std::cout << *iterator << '\n';
    std::cout << (iterator == vector.begin()) << (iterator == vector2.begin()) << '\n';
    return 0;
}