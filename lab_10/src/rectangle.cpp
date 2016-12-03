#include "rectangle.h"

Rectangle::Rectangle(int id, int x, int y, int width, int height):Figure(id, x, y)
{
    this->width = width;
    this->height = height;
}

Rectangle::~Rectangle(){};

void Rectangle::print() const
{
    printf("Rectangle %i: x = %i y = %i width = %i height = %i\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const
{
    return abs(x - get_x()) * 2 <= width && abs(y - get_y()) * 2 <= height;
}

void Rectangle::zoom(int factor)
{
    width *= factor;
    height *= factor;
}
