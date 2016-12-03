#pragma once

#include "figure.h"
#include <cstdio>
#include <stdlib.h>

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    virtual ~Rectangle();

    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    virtual void zoom(int factor);
    private:
        int width;
        int height;
};
