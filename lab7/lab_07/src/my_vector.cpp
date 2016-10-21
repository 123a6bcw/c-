#include "my_vector.h"

MyVector::MyVector()
{
    this -> _data = new int[0];
}

MyVector::MyVector(std::size_t init_capacity)
{
    this -> _data = new int[init_capacity];
    this -> _cp = init_capacity;
}

MyVector::~MyVector()
{
    delete(this -> _data);
}

void MyVector::set(std::size_t index, int value)
{
    *(this -> _data + index) = value; 
}

int MyVector::get(std::size_t index)
{
    return *(this -> _data + index);
}

std::size_t MyVector::size()
{
    return this -> _sz;
}

std::size_t MyVector::capacity()
{
    return this -> _cp;
}

void MyVector::reserve(std::size_t new_capacity)
{
    int *_data_new = new int[new_capacity];
    for (std::size_t i = 0; i < (this -> _sz); i++)
        *(_data_new + i) = *((this -> _data) + i);
    delete(_data);
    this -> _data = _data_new; 
    this -> _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size)
{
    if (new_size < (this -> _sz))
    {
        this -> _sz = new_size;
    }
    
    if (new_size > (this -> _cp))
    {
        this -> reserve(2 * new_size);
    }
    
    for (std::size_t i = (this -> _sz); i < new_size; i++)
    {
        this -> push_back(0);
    }
}

void MyVector::push_back(int value)
{
    if ((this -> _sz) + 1 >= this -> _cp)
    {
        this -> reserve(2 * (this -> _cp));
    }
    
    *((this -> _data) + (this -> _sz)) = value;
    (this -> _sz)++;
}

void MyVector::insert(std::size_t index, int value)
{
    if ((this -> _sz) == 0)
    {
        this -> push_back(value);
        return;
    }
    
    if (this -> _sz + 1 >= this -> _cp)
    {
        this -> reserve(2 * (this -> _cp));
    }
    
    for (std::size_t i = (this -> _sz); i > index; i--)
    {
        *((this -> _data) + i) = *((this -> _data) + i - 1);
    }
    
    *((this -> _data) + index) = value;
    (this -> _sz)++;
}

void MyVector::erase(std::size_t index)
{ 
    for (std::size_t i = index + 1; i <= (this -> _sz) - 1; i++)
    {
        (*((this -> _data) + i - 1)) = (*((this -> _data) + i));
    }
    
    (this -> _sz)--;
}
