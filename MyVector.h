template <class T>
class MyVector
{
private:
    T *_data;
    int _length;
    int _capacity;

    class VectorIterator
    {
    private:
    friend MyVector;
        MyVector<T> *_vector;
        int _index;
        void Validate();
    public:
        VectorIterator(MyVector<T> &vector, int index) : _vector(&vector), _index(index){};
        virtual MyVector<T> &origin();
        virtual bool operator==(MyVector<T>::VectorIterator It) { return _vector == It._vector && _index == It._index; };
        virtual bool operator!=(MyVector<T>::VectorIterator It) { return !(*this == It); };
        virtual MyVector<T>::VectorIterator operator++();
        virtual MyVector<T>::VectorIterator operator++(int) { return ++(*this); };
        virtual MyVector<T>::VectorIterator operator--();
        virtual MyVector<T>::VectorIterator operator--(int) { return --(*this); };
        virtual T operator*();
        virtual void operator=(T val);
    };

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

// MyVector::VectorIterator method implementations
template <class T>
void MyVector<T>::VectorIterator::Validate()
{
    if (_vector->length() < _index)
    {
        throw "Iterator invalid";
    }
}
template <class T>
MyVector<T> &MyVector<T>::VectorIterator::origin()
{
    return *_vector;
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator++()
{
    VectorIterator out(*_vector, ++_index);
    return out;
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::VectorIterator::operator--()
{
    VectorIterator out(*_vector, --_index);
    return out;
}
template <class T>
T MyVector<T>::VectorIterator::operator*()
{
    Validate();
    return _vector->at(_index);
}
template <class T>
void MyVector<T>::VectorIterator::operator=(T val)
{
    Validate();
    (_vector->at(_index)) = val;
}

// MyVector method implementations
template <class T>
MyVector<T>::MyVector() : _data(new T[1]), _length(0), _capacity(1) {}
template <class T>
MyVector<T>::MyVector(const MyVector<T> &other) : _length(other._length), _capacity(other._capacity)
{
    _data = new T[_capacity];
    for (int i = 0; i < _length; i++)
    {
        _data[i] = other._data[i];
    }
}
template <class T>
MyVector<T>::MyVector(T *array, int length) : _length(length)
{
    _capacity = 1;
    while (_capacity < _length)
    {
        _capacity *= 2;
    }
    _data = new T[_capacity];
    for (int i = 0; i < length; i++)
    {
        _data[i] = array[i];
    }
}

template <class T>
MyVector<T>::MyVector(const MyVector<T>::VectorIterator begin, const MyVector<T>::VectorIterator end)
{
    _data = new T[1];
    _length = 0;
    _capacity = 1;
    reserve(end._index - begin._index);
    for(auto i = begin; i != end; ++i)
    {
        push_back(*i);
    }
}
template <class T>
MyVector<T>::~MyVector()
{
    delete[] _data;
}
template <class T>
void MyVector<T>::operator=(const MyVector<T> &other)
{
    _length = other._length;
    _capacity = other._capacity;
    delete[] _data;
    _data = new T[_capacity];
    for (int i = 0; i < _length; i++)
    {
        _data[i] = other._data[i];
    }
}
template <class T>
bool MyVector<T>::operator==(const MyVector<T> &other)
{
    if (_length != other._length)
    {
        return false;
    }
    for (int i = 0; i < _length; ++i)
    {
        if (_data[i] != other._data[i])
        {
            return false;
        }
    }
    return true;
}
template <class T>
bool MyVector<T>::operator!=(const MyVector<T> &other)
{
    return !(*this == other);
}
template <class T>
bool MyVector<T>::empty()
{
    return _length == 0;
}
template <class T>
int MyVector<T>::size()
{
    return _length;
}
template <class T>
int MyVector<T>::length()
{
    return _length;
}
template <class T>
int MyVector<T>::capacity()
{
    return _capacity;
}
template <class T>
T& MyVector<T>::at(int index)
{
    if (index < 0 || index >= _length)
    {
        throw "out of range";
    }
    else
    {
        return _data[index];
    }
}
template <class T>
T& MyVector<T>::operator[](int index)
{
    return _data[index];
}
template <class T>
T& MyVector<T>::front()
{
    return _data[0];
}
template <class T>
T& MyVector<T>::back()
{
    return _data[_length - 1];
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::begin()
{
    VectorIterator out(*this, 0);
    return out;
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::end()
{
    VectorIterator out(*this, _length);
    return out;
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::iteratorAt(int index)
{
    VectorIterator out(*this, index);
    return out;
}
template <class T>
typename MyVector<T>::VectorIterator MyVector<T>::operator()(int index)
{
    VectorIterator out(*this, index);
    return out;
}
template <class T>
void MyVector<T>::clear()
{
    delete[] _data;
    _length = 0;
    _capacity = 1;
    _data = new T[1];
}
template <class T>
void MyVector<T>::push_back(T element)
{
    if (_length + 1 > _capacity)
    {
        _capacity *= 2;
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        data[_length] = element;
        delete[] _data;
        _data = data;
    }
    else
    {
        _data[_length] = element;
    }
    _length++;
}
template <class T>
void MyVector<T>::pop_back()
{
    _length--;
    if (_length <= _capacity / 2)
    {
        _capacity /= 2;
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::reserve(int count)
{
    if (_length + count > _capacity)
    {
        while (_length + count > _capacity)
        {
            _capacity *= 2;
        }
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::shrink()
{
    if (_length == 0)
    {
        clear();
        return;
    }
    if (_length < _capacity / 2)
    {
        while (_length < _capacity / 2)
        {
            _capacity /= 2;
        }
        T *data = new T[_capacity];
        for (int i = 0; i < _length; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }
}
template <class T>
void MyVector<T>::insert(int index, T element, int count)
{
    if (index >= _length + 1 || index < 0)
    {
        throw "invalid insert index";
    }
    if (count < 0)
    {
        throw "inserting negative amount of elements";
    }
    reserve(count);
    _length += count;
    for (int i = _length - 1; i >= index + count; i--)
    {
        _data[i] = _data[i - count];
    }
    for (int i = index; i < index + count; i++)
    {
        _data[i] = element;
    }
}
template <class T>
void MyVector<T>::insert(int index, T *array, int length)
{
    if (index >= _length + 1 || index < 0)
    {
        throw "invalid insert index";
    }
    reserve(length);
    _length += length;
    for (int i = index; i < index + length; i++)
    {
        _data[i + length] = _data[i];
        _data[i] = array[i - index];
    }
}
template <class T>
void MyVector<T>::insert(int index, const MyVector<T> &vector)
{
    insert(index, vector._data, vector._length);
}
template <class T>
void MyVector<T>::insert(int index, const MyVector<T>::VectorIterator begin, const MyVector<T>::VectorIterator end)
{
    MyVector<T> vector(begin, end);
    insert(index, vector);
}
template <class T>
void MyVector<T>::erase(int index, int count)
{
    if (index < 0 || index >= _length)
    {
        throw "invalid erase index";
    }
    if (count < 0)
    {
        throw "erasing negative amount of elements";
    }
    if (count + index >= _length)
    {
        count = _length - index;
    }
    for (int i = index; i + count < _length; i++)
    {
        _data[i] = _data[i + count];
    }
    _length -= count;
    shrink();
}
template <class T>
template <class T2>
MyVector<T2> MyVector<T>::map(T2 (*function)(T))
{
    MyVector<T2> result;
    result.reserve(_length);
    for (int i = 0; i < _length; ++i)
    {
        result.push_back(function(_data[i]));
    }
    return result;
}
template <class T>
void MyVector<T>::map(void (*function)(T&))
{
    for (int i = 0; i < _length; ++i)
    {
        function(_data[i]);
    }
}
template <class T>
void MyVector<T>::filter(bool (*predicate)(T))
{
    T* data = new T[_length];
    int j = 0;
    for (int i = 0; i < _length; ++i)
    {
        if(predicate(_data[i]))
        {
            data[j] = _data[i];
            ++j;
        }
    }
    _length = j;
    delete _data;
    _data = data;
    shrink();
}