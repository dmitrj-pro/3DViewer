#ifndef LINE
#define LINE

#include "point.h"
#include "2doperation.h"

template <typename T>
class Line{
    private:
        Point<T> start;
        Point<T> end;
    public:
        Line(){}
        DP_add_getter_name(Point<T>, start, Start)
        DP_add_getter_name(Point<T>, end, End)
        Line(const Point<T> & start, const Point<T> & end):start(start), end(end){}
        /// Сместить линию в двумерном пространстве
        /// <param name="x">Смещение по х</param>
        /// <param name="y">Смещение по у</param>
        inline void Offset(const T& x, const T & y){
            start = Offset(start, x, y);
            end = Offset(end, x,y);
        }

        /// Смещение линии в трехмерном пространстве
        /// <param name="x">Смещение по х</param>
        /// <param name="y">Смещение по у</param>
        /// <param name="z">Смещение по z</param>
        inline void Offset(const T & x, const T & y, const T & z){
            start - Offset(start, x, y, z);
            end = Offset(end, x, y, z);
        }

        /// Поворот линии в ДВУМЕРНОМ прастарнстве
        /// <param name="d">Угол поворота</param>
        inline void Rotate2D(const T & x){
            start = Rotate2D(start, x);
            end = Rotate2D(end, x);
        }

        /// Поворот линии вокруг оси OX
        /// <param name="d">Угол поворота</param>
        inline void Rotate3Dx(const T & x){
            start = Operation::Rotate3Dx(start, x);
            end = Operation::Rotate3Dx(end, x);
        }

        /// Поворот линии вокруг оси OY
        /// <param name="d">Угол поворота</param>
        inline void Rotate3Dy(const T & x){
            start = Operation::Rotate3Dy(start, x);
            end = Operation::Rotate3Dy(end, x);
        }

        /// Поворот линии вокруг оси OZ
        /// <param name="d">Угол поворота</param>
        inline void Rotate3Dz(const T & x){
            start = Operation::Rotate3Dz(start, x);
            end = Operation::Rotate3Dz(end, x);
        }

        /// Изменение размера точки (В 3D НЕ ПРИМЕНЯТЬ)
        /// <param name="s">Size.</param>
        inline void Scale(const T & x){
            start = Scale(start, x);
            end = Scale(end, x);
        }

        /// Масштабирование в пространстве
        /// <param name="x">Новый масштаб по х</param>
        /// <param name="y">Новый масштаб по у</param>
        /// <param name="z">Новый масштаб по z</param>
        inline void Scale(const T & x, const T & y, const T & z){
            start= Scale(start, x, y, z);
            end= Scale(end, x, y, z);
        }


};

#endif // LINE

