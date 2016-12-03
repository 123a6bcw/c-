#include <stdio.h>

#include "scheme.h"
#include "rectangle.h"
#include "circle.h"

void my_test()
{
    printf("\n");
    Scheme scheme(10);
    scheme.push_back_figure(new Rectangle(1, 1, 1, 1, 1));
    scheme.push_back_figure(new Circle(2, 1, 1, 1, ""));
    scheme.print_all_figures();
    scheme.is_inside_figure(1, 1)->print();
    scheme.move(1, 2, 2);
    scheme.print_all_figures();
    scheme.is_inside_figure(1, 1)->print();
    scheme.move(2, 0, 0);
    scheme.zoom_figure(2, 100);
    scheme.print_all_figures();
    scheme.is_inside_figure(1, 1)->print();
    scheme.zoom_figure(1, 2);
    scheme.is_inside_figure(1, 1)->print();
    scheme.push_back_figure(new Rectangle(4, 1, 1, 1, 1));
    scheme.push_back_figure(new Circle(5, 1, 1, 1, "n2"));
    scheme.remove_figure(4);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();
    scheme.remove_figure(2);
    scheme.print_all_figures();
    scheme.remove_figure(5);
    scheme.print_all_figures();
    scheme.push_back_figure(new Rectangle(1, 0, 0, 5, 5));
    scheme.push_back_figure(new Rectangle(2, 100, 100, 6, 6));
    scheme.is_inside_figure(2, 2)->print();
    printf("%i\n", scheme.is_inside_figure(3, 3) == NULL);
    scheme.is_inside_figure(103, 97)->print();
    scheme.is_inside_figure(103, 100)->print();
    scheme.push_back_figure(new Circle(3, -100, -100, 5, "ya krug"));
    scheme.is_inside_figure(-100, -100)->print();
    scheme.is_inside_figure(-105, -100)->print();
    scheme.is_inside_figure(-100, -95)->print();
}

int main() {
    Scheme scheme(10);
    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

    scheme.print_all_figures();

    Figure* found = scheme.is_inside_figure(5, 5);
    if (found != 0) {
        found->print();
    }
    else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();
    
    //my_test();
    return 0;
}
