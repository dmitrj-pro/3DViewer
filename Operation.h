#ifndef DOPERATION
#define DOPERATION

#include "Matrix.h"
#include "Point.h"
#include <cmath>
#include <iostream>

namespace Operation {

    template <typename T>
    inline Point<T> ToPoint(const Matrix<T> & m){
        if (m.GetM() >= 4)
            return Point<T>(m.Get(0, 0) / m.Get(3, 0), m.Get(1, 0) / m.Get(3, 0), m.Get(2, 0) / m.Get(3, 0));

        if (m.GetN() >= 4)
            return Point<T>(m.Get(0, 0) / m.Get(0, 3), m.Get(0, 1) / m.Get(0, 3), m.Get(0, 2) / m.Get(0, 3));

        if (m.GetM() == 3) {
            return Point<T>(m.Get(0, 0) / m.Get(2, 0), m.Get(1, 0)/ m.Get(2, 0));
        } else {
            return Point<T>(m.Get(0, 0) / m.Get(0, 2), m.Get(0, 1) / m.Get(0, 2));
        }
    }

    /// Получение матрицы смещения для двумерного случая
    /// <param name="x"Смещение по х</param>
    /// <param name="y">Смещение по у</param>
    template <typename T>
    inline Matrix<T> GetMOffset(const T & x, const T & y){
        Matrix<T> res = Matrix<T>(3, 3);
        res.Set(0, 0, 1);
        res.Set(1, 1, 1);
        res.Set(2, 2, 1);
        res.Set(2, 0, x);
        res.Set(2, 1, y);
        return res;
    }

    /// Получение матрицы для трехмерного случая
    /// <param name="x">Смещение по x</param>
    /// <param name="y">Смещение по у</param>
    /// <param name="z">Смещение по z</param>
    template <typename T>
    inline Matrix<T> GetMOffset(const T & x, const T & y, const T & z){
        Matrix<T> p = Matrix<T>(4, 4);
        p.Set(0, 0, 1);
        p.Set(1, 1, 1);
        p.Set(2, 2, 1);
        p.Set(3, 3, 1);
        p.Set(3, 0, x);
        p.Set(3, 1, y);
        p.Set(3, 2, z);
        return p;
    }

    /// Получение матрицы поворота
    /// <param name="x">Угол, на который повернуть</param>
    template <typename T>
    inline Matrix<T> GetMRotate2D(const T & x){
        Matrix<T> p = Matrix<T>(3, 3);
        p.Set(0, 0, cos(x));
        p.Set(0, 1, sin(x));
        p.Set(1, 0, sin(x) * (-1));
        p.Set(1, 1, cos(x));
        p.Set(2, 2, 1);
        return p;
    }

    /// Получение матрицы поворота по X
    /// <param name="x">K.</param>
    template <typename T>
    inline Matrix<T> GetMRotateX(const T & x){
        Matrix<T> res = Matrix<T>(4, 4);
        res.Set(0, 0, 1);
        res.Set(3, 3, 1);
        res.Set(1, 1, cos(x));
        res.Set(1, 2, sin(x) * (-1));
        res.Set(2, 1, sin(x));
        res.Set(2, 2, cos(x));


        return res;
    }

    /// Получение матрицы поворота по Y
    /// <param name="x">Угол поворота<param>
    template <typename T>
    inline Matrix<T> GetMRotateY(const T &x){
        Matrix<T> res = Matrix<T>(4, 4);
        res.Set(0, 0, cos(x));
        res.Set(0, 2, sin(x));
        res.Set(1, 1, 1);
        res.Set(2, 0, (-1) * sin(x));
        res.Set(2, 2, cos(x));
        res.Set(3, 3, 1);
        return res;
    }

    /// Получение матрицы поворота по Z
    /// <param name="x">Угол поворота<param>
    template <typename T>
    inline Matrix<T> GetMRotateZ(const T & x){
        Matrix<T> res = Matrix<T>(4, 4);
        res.Set(0, 0, cos(x));
        res.Set(0, 1, (-1) * sin(x));
        res.Set(1, 0, sin(x));
        res.Set(1, 1, cos(x));
        res.Set(2, 2, 1);
        res.Set(3, 3, 1);
        return res;
    }

    template <typename T>
    inline Matrix<T> GetMScale(const T & x){
        Matrix<T> res = Matrix<T>(3, 3);
        res.Set(0, 0, x);
        res.Set(1, 1, x);
        res.Set(2, 2, 1);
        return res;
    }

    /// Получение матрицы для изменния размера
    /// <param name="x">Изменение размера по X</param>
    /// <param name="y">Изменение размера по Y</param>
    /// <param name="z">Изменение размера по Z</param>
    template <typename T>
    inline Matrix<T> GetMScale(const T & x, const T & y, const T & z){
        Matrix<T> res = Matrix<T>(4, 4);
        res.Set(0, 0, x);
        res.Set(1, 1, y);
        res.Set(2, 2, z);
        res.Set(3, 3, 1);
        return res;
    }



    /// Поворот вокруг оси OX
    /// <param name="x">The x coordinate.</param>
    template <typename T>
    inline Point<T> Rotate3Dx(const Point<T> & p, const T & x){
        return ToPoint(p.ToMatrix() * GetMRotateX(x));
    }

    /// Поворот вокруг оси OY
    /// <param name="d">Угол поворота</param>
    template <typename T>
    inline Point<T> Rotate3Dy(const Point<T> & p, const T & x){
        return ToPoint(p.ToMatrix() * GetMRotateY(x));
    }

    /// Повотор вокруг оси OZ
    /// <param name="z">Угол поворота</param>
    template <typename T>
    inline Point<T> Rotate3Dz(const Point<T> & p, const T & x){
        return ToPoint(p.ToMatrix() * GetMRotateZ(x));
    }


    /// Сместить точку в двумерном пространстве
    /// <param name="x">Смещение по х</param>
    /// <param name="y">Смещение по у</param>
    template <typename T>
    inline Point<T> Offset(const Point <T> & p, const T & x, const T & y){
        return ToPoint(p.ToMatrix() * GetMOffset(x, y));
    }

    /// Смещение точки в трехмерном пространстве
    /// <param name="x">Смещение по х</param>
    /// <param name="y">Смещение по у</param>
    /// <param name="z">Смещение по z</param>
    template <typename T>
    inline Point<T> Offset(const Point <T> & p, const T & x, const T & y, const T & z){
        return ToPoint(p.ToMatrix() * GetMOffset(x, y, z));
    }

    template <typename T>
    inline T SMult(const Point<T> & p1, const Point<T> p2){
        T res = p1.GetX() * p2.GetX();
        res += p1.GetY() * p2.GetY();
        res += p1.GetZ() * p2.GetZ();
        return res;
    }

    template <typename T>
    inline T Ugol(const Point<T> & vec1, const Point<T> & vec2){
        T a = SMult(vec1, vec2);
        T l1 = vec1.Length();
        T l2 = vec2.Length();
        T co = a/ (l1 * l2);
        return acos(co);
    }

    /// Повернуть точку вокруг оси координат
    /// <param name="d">Угол поворота</param>
    template <typename T>
    inline Point<T> Rotate2D(const Point<T> & p, const T & d){
        return ToPoint(p.ToMatrix() * GetMRotate2D(d));
    }

    /// Изменение размера точки (В 3D НЕ ПРИМЕНЯТЬ)
    /// <param name="size">Size.</param>
    template <typename T>
    inline Point<T> Scale(const Point<T> & p, const T & size){
        return ToPoint(p.ToMatrix() * GetMScale(size));
    }

    /// Масштабирование в пространстве
    /// <param name="x">Новый масштаб по х</param>
    /// <param name="y">Новый масштаб по у</param>
    /// <param name="z">Новый масштаб по z</param>
    template <typename T>
    inline Point<T> Scale(const Point<T> & p, const T & x, const T & y, const T & z){
        return ToPoint(p.ToMatrix() * GetMScale(x, y, z));
    }




    /*
    public double Det(){
        double det = 1;
        const double EPS = 1E-9;
        double[][] b = new double[1][];
        b[0] = new double[_n];
        //проходим по строкам
        for (int i=0; i<_n; ++i) {
            //присваиваем k номер строки
            int k = i;
            //идем по строке от i+1 до конца
            for (int j=i+1; j<_n; ++j)
                //проверяем
                if (Math.Abs(_matr[j] [i]) > Math.Abs(_matr[k][i]))
                    //если равенство выполняется то k присваиваем j
                    k = j;
            //если равенство выполняется то определитель приравниваем 0 и выходим из программы
            if (Math.Abs(_matr[k] [i]) < EPS) {
                det = 0;
                break;
            }
            //меняем местами a[i] и a[k]
            b[0] = _matr[i];
            _matr[i] = _matr[k];
            _matr[k] = b[0];
            //если i не равно k
            if (i != k)
                //то меняем знак определителя
                det = -det;
            //умножаем det на элемент a[i][i]
            det *= _matr[i][i];
            //идем по строке от i+1 до конца
            for (int j=i+1; j<_n; ++j)
                //каждый элемент делим на a[i][i]
                _matr[i][j] /= _matr[i][i];
            //идем по столбцам
            for (int j=0; j<_n; ++j)
                //проверяем
                if ((j != i)&&(Math.Abs(_matr[j][i]) > EPS))
                    //если да, то идем по k от i+1
                    for (k = i+1; k < _n; ++k)
                        _matr[j][k] -= _matr[i][k] * _matr[j][i];
        }
        return det;
    }
    */
}
#endif // 2DOPERATION

