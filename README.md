# MyVector

This is my simplified alternative for std::vector. It was created as an exercise and is not really supposed to be used.

## Main.cpp

Contains main() intended to showcase most of what this library has to offer.

## MyVector.h

Actual library. Public methods of avalible classes are pretty self-explanatory.

### MyVector

```cpp
template <class T>
class MyVector
{
public:
//metods are mostly analogs for functionality of std::vector with established names
    MyVector();
    MyVector(const MyVector<T> &other);
    MyVector(T *array, int length);
    MyVector(const MyVector<T>::VectorIterator begin, const MyVector<T>::VectorIterator end);
    ~MyVector();
    void operator=(const MyVector<T> &other);
    bool operator==(const MyVector<T> &other);
    bool operator!=(const MyVector<T> &other);
    bool empty();
    int size();
    int length();
    int capacity();
    T& at(int index); //[] but with boundary check
    T& operator[](int index);
    T& front();
    T& back();
    MyVector<T>::VectorIterator begin();
    MyVector<T>::VectorIterator end();
    MyVector<T>::VectorIterator iteratorAt(int index); //gives an iterator to an element at desired index
    MyVector<T>::VectorIterator operator()(int index); //synonym to iteratorAt
    void clear();
    void push_back(T element);
    void pop_back();
    void reserve(int count); //ensures there is enough space reserved to contain at least length() + count elements without copying anything to new internal array. Can be used to save time when pushing back known amount of elements. Mostly for internal use
    void shrink(); //frees unused space that could be created by use of reserve. Mostly internal
    void insert(int index, T element, int count = 1);
    void insert(int index, T *array, int length);
    void insert(int index, const MyVector<T> &vector);
    void insert(int index, const MyVector<T>::VectorIterator begin, const MyVector<T>::VectorIterator end);
    void erase(int index, int count = 1);
    void map(void (*function)(T&)); //applies function to each element
    template <class T2> MyVector<T2> map(T2 (*function)(T)); //returns vector such that v2[i] == function(v[i])
    void filter(bool (*predicate)(T)); //deletes all elements for which predicate returns false
};
```

### VectorIterator

Is a private class so it can't be constructed. Instead, you should use MyVector methods to create instances of MyVector::VectorIterator

```cpp
class VectorIterator
{
public:
    virtual MyVector<T> &origin(); //gives back the container this iterator was created from
    virtual bool operator==(MyVector<T>::VectorIterator It);
    virtual bool operator!=(MyVector<T>::VectorIterator It);
    virtual MyVector<T>::VectorIterator operator++(); //moves iterator forward
    virtual MyVector<T>::VectorIterator operator++(int);
    virtual MyVector<T>::VectorIterator operator--(); //moves iterator back
    virtual MyVector<T>::VectorIterator operator--(int);
    virtual T operator*(); //evaluates iterator
    virtual void operator=(T val); //sets value
};
```
