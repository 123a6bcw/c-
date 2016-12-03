#include "scheme.h"
#include <stdio.h>
Scheme::Scheme(int capacity)
{
    figures_ = new Figure* [capacity]();
}

Scheme::~Scheme()
{
    for (std::size_t i = 0; figures_[i] != NULL; i++)
    {
        delete figures_[i];
    }
    
    delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg)
{
    std::size_t i;
    for (i = 0; figures_[i] != NULL; i++);
    figures_[i] = fg;
}

void Scheme::remove_figure(int id)
{
    for (std::size_t i = 0; figures_[i] != NULL; i++)
    {
        if (figures_[i]->get_id() == id)
        {
            delete figures_[i];
            figures_[i] = NULL;
            for (; figures_[i + 1] != NULL; i++)
            {
                std::swap(figures_[i], figures_[i + 1]);
            }
            
            return;
        }
    }
}

void Scheme::print_all_figures()
{
    for (std::size_t i = 0; figures_[i] != NULL; i++)
    {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor)
{
    get_by_id(id)->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y)
{
    for (std::size_t i = 0;;i++)
    {
        if (figures_[i]->is_inside(x, y))
        {
            return figures_[i];
        }
    }
}

void Scheme::move(int id, int new_x, int new_y)
{
    get_by_id(id)->move(new_x, new_y);
}

Figure* Scheme::get_by_id(int id)
{
    for (std::size_t i = 0; figures_[i] != NULL; i++)
    {
        if (figures_[i]->get_id() == id)
        {
            return figures_[i];
        }
    }
    
    return NULL;
}