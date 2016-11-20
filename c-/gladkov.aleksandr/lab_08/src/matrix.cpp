#include "matrix.h"

Matrix::Matrix(std::size_t r, std::size_t c)
{
    this->_rows = r;
    this->_cols = c;
    this->_data = new int* [r];
    int* data_map = new int [r * c]();
    std::size_t i;
    for (i = 0; i < r; i++)
    {
        this->_data[i] = data_map + i * c;
    }
}

Matrix::Matrix(const Matrix& that)
{
    this->_rows = that._rows;
    this->_cols = that._cols;
    this->_data = new int* [that._rows];
    int* data_map = new int [that._rows * that._cols]();
    std::size_t i;
    for (i = 0; i < that._rows; i++)
    {
        this->_data[i] = data_map + i * that._cols;
    }
    
    for (i = 0; i < that._rows; i++)
    {
        std::size_t j;
        for (j = 0; j < that._cols; j++)
        {
            this->_data[i][j] = that._data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    delete [] *(this->_data);
    delete [] this->_data;
}

Matrix& Matrix::operator=(const Matrix& that)
{
    if (this == &that)
    {
        return *this;
    }
    
    Matrix new_matrix(that);
    std::swap(this->_rows, new_matrix._rows);
    std::swap(this->_cols, new_matrix._cols);
    std::swap(this->_data, new_matrix._data);
    
    return *this;
}

std::size_t Matrix::get_rows()
{
    return this->_rows;
}

std::size_t Matrix::get_cols()
{
    return this->_cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val)
{
    this->_data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const
{
    return this->_data[i][j];
}

void Matrix::print(FILE* f) const
{
    std::size_t i;
    for (i = 0; i < this->_rows; i++)
    {
        std::size_t j;
        for (j = 0; j < this->_cols; j++)
        {
            fprintf(f, "%i", this->_data[i][j]);
            if (j + 1 < this->_cols)
            {
                fprintf(f, " ");
            } else
            {
                fprintf(f, "\n");
            }
        }
    }
}

bool Matrix::operator==(const Matrix& that) const
{
    if (this->_rows != that._rows || this->_cols != that._cols)
    {
        return false;
    }
    
    std::size_t i;
    for (i = 0; i < this->_rows; i++)
    {
        std::size_t j;
        for (j = 0; j < this->_cols; j++)
        {
            if (this->_data[i][j] != that._data[i][j])
            {
                return false;
            }
        }
    }
    
    return true;
}

bool Matrix::operator!=(const Matrix& that) const
{
    return !(*this == that);
}

Matrix& Matrix::operator+=(const Matrix& that)
{
    std::size_t i;
    for (i = 0; i < this->_rows; i++)
    {
        std::size_t j;
        for (j = 0; j < this->_cols; j++)
        {
            this->_data[i][j] += that._data[i][j];
        }
    }
    
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& that)
{
    std::size_t i;
    for (i = 0; i < this->_rows; i++)
    {
        std::size_t j;
        for (j = 0; j < this->_cols; j++)
        {
            this->_data[i][j] -= that._data[i][j];
        }
    }
    
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& that)
{
    return *this = *this * that;
}

Matrix Matrix::operator+(const Matrix& that) const
{
    return Matrix(that) += *this;
}

Matrix Matrix::operator-(const Matrix& that) const
{
    return Matrix(that) -= *this;
}

Matrix Matrix::operator*(const Matrix& that) const
{
    Matrix res(this->_rows, that._cols);
    std::size_t i;
    for (i = 0; i < this->_rows; i++)
    {
        std::size_t j;
		for (j = 0; j < that._cols; j++)
	    {
	        std::size_t k;
			for (k = 0; k < this->_cols; k++)
			{
		    	res._data[i][j] += this->_data[i][k] * that._data[k][j];
		    }
		}
    }
    
    return res;
}
