#ifndef POINT
#define POINT

#include <DPLib.conf.h>
#include "matrix.h"
#include <Generator/CodeGenerator.h>
#include <cmath>

template <typename T>
class Point{
    private:
        T x;
        T y;
        T z;
        inline void Save(const Point & p){
            x = p.x;
            y = p.y;
            z = p.z;
        }

    public:
        Point(){}
        Point(const T & x, const T & y): x(x), y(y){}
        Point(const Point & p):x(p.x), y(p.y), z(p.z) {}
        Point(const T &x, const T &y, const T &z): x(x), y(y), z(z){}
        DP_add_getter_setter_name(T, x, X)
        DP_add_getter_setter_name(T, y, Y)
        DP_add_getter_setter_name(T, z, Z)

        inline Matrix<T> ToMatrix2D()const {
            Matrix<T> p2 = Matrix<T>(3, 1);
            p2.Set(0, 0, x);
            p2.Set(0, 1, y);
            p2.Set(0, 3, 1);
        }

        inline Matrix<T> ToMatrix() const {
            Matrix<T> res = Matrix<T>(4, 1);
            res.Set(0, 0, x);
            res.Set(0, 1, y);
            res.Set(0, 2, z);
            res.Set(0, 3, 1);
            return res;
        }
        template <typename Ostream>
        friend inline  Ostream & operator << (Ostream & os, const Point & p){
            os << "(" << p.x<< ", " << p.y << ", " << p.z << ")";
        }
        friend inline bool operator==(const Point & p1, const Point & p2){
            return (p2.x == p1.x) && (p2.y == p1.y) && (p2.z == p1.z);
        }

        // Длина вектора
        inline T Length()const{
            return sqrt (x * x + y * y + z * z);
        }


};

#endif // POINT

