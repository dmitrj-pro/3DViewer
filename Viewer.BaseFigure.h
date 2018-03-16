#ifndef BASE_FIGURE
#define BASE_FIGURE

#include "Figure.h"
#include <cmath>


template <typename T>
inline void Hexahedron(Figure<T> & _figure){
    _figure.clear();
    Point<T> p1 = Point<T>(100 / 2, -100 / 2, 100 / 2);
    Point<T> p2 = Point<T>(100 / 2, -100 / 2, -100 / 2);
    Point<T> p3 = Point<T>(-100 / 2, -100 / 2, -100 / 2);
    Point<T> p4 = Point<T>(-100 / 2, -100 / 2, 100 / 2);

    Point<T> p5 = Point<T>(100 / 2, 100 / 2, 100 / 2);
    Point<T> p6 = Point<T>(100 / 2, 100 / 2, -100 / 2);
    Point<T> p7 = Point<T>(-100 / 2, 100 / 2, -100 / 2);
    Point<T> p8 = Point<T>(-100 / 2, 100 / 2, 100 / 2);

    // Должна быть именно такая последовательность описания, иначе отображается не совсем корректно
    _figure.Add(Line<T>(p1, p2));
    _figure.Add(Line<T>(p2, p3));
    _figure.Add(Line<T>(p1, p5));
    _figure.Add(Line<T>(p2, p6));

    _figure.Add(Line<T>(p3, p4));
    _figure.Add(Line<T>(p4, p1));
    _figure.Add(Line<T>(p7, p8));

    _figure.Add(Line<T>(p5, p6));
    _figure.Add(Line<T>(p6, p7));
    _figure.Add(Line<T>(p8, p5));
    _figure.Add(Line<T>(p3, p7));
    _figure.Add(Line<T>(p4, p8));
}

template <typename T>
inline void Tetrahedron(Figure<T> & figure){
    figure.clear();
    double coef = 50 * sqrt(3);
    Point<T> p1 = Point<T>(0, coef / 2, 0);
    Point<T> p2 = Point<T>(-50, -coef / 2, 0);
    Point<T> p3 = Point<T>(50, -coef / 2, 0);
    Point<T> p4 = Point<T>(0, -coef / 2, -coef);

    // Должна быть именно такая последовательность описания, иначе отображается не совсем корректно
    figure.Add(Line<T>(p3, p4));
    figure.Add(Line<T>(p2, p4));
    figure.Add(Line<T>(p3, p1));
    figure.Add(Line<T>(p2, p3));
    figure.Add(Line<T>(p1, p4));
    figure.Add(Line<T>(p1, p2));
}


#endif // BASE_FIGURE

