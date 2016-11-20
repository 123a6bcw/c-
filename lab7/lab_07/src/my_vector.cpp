#include "my_vector.h"

MyVector::MyVector()
{
    this -> _data = new int[2];
    *(_data) = 0;
    *(_data + 1) = 0;
    
    this -> _sz = 0;
    this -> _cp = 2;
}

MyVector::MyVector(std::size_t init_capacity)
{
    (this -> _data) = new int[init_capacity];
    
    for (std::size_t i = 0; i < init_capacity; i++)
    {
        *((this -> _data) + i) = 0;
    }
    
    (this -> _cp) = init_capacity;
    (this -> _sz) = 0;
}

MyVector::~MyVector()
{
    delete [] (this -> _data);
}

void MyVector::set(std::size_t index, int value)
{
    *((this -> _data) + index) = value; 
}

int MyVector::get(std::size_t index)
{
    return *((this -> _data) + index);
}

std::size_t MyVector::size()
{
    return (this -> _sz);
}

std::size_t MyVector::capacity()
{
    return (this -> _cp);
}

void MyVector::reserve(std::size_t new_capacity)
{
    if (new_capacity <= (this -> _cp))
    {
        return;
    }
    
    int *_data_new = new int[new_capacity];
    for (std::size_t i = 0; i < (this -> _sz); i++)
    {    
        *(_data_new + i) = *((this -> _data) + i);
    }
    
    for (std::size_t i = (this -> _sz); i < new_capacity; i++)
    {
        *(_data_new + i) = 0;
    }
    
    delete [] (this -> _data);
    (this -> _data) = _data_new; 
    
    if (new_capacity > (this -> _cp))
    {
        (this -> _cp) = new_capacity;
    }
}

void MyVector::resize(std::size_t new_size)
{
    if (new_size < (this -> _sz))
    {
        (this -> _sz) = new_size;
        return;
    }
    
    if (new_size > (this -> _cp))
    {
        std::size_t _new_capacity = (this -> _cp);
        while (_new_capacity < new_size)
        {
            _new_capacity *= 2;
        }
        
        this -> reserve(_new_capacity);
    }
    
    (this -> _sz) = new_size;
}

void MyVector::push_back(int value)
{
    if ((this -> _sz) + 1 > this -> _cp)
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
    
    if ((this -> _sz) + 1 > (this -> _cp))
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
        *((this -> _data) + i - 1) = *((this -> _data) + i);
    }
    
    (this -> _sz)--;
}
