#ifndef FACE_
#define FACE_

#include <DPLib.conf.h>
#include <Generator/CodeGenerator.h>
#include "Point.h"
#include "Matrix.h"
#include <Types/Exception.h>
#include <Converter/Converter.h>

using DP::List;

template <typename T>
struct Voth{
    T A;
    T B;
    T C;
    T D;
};

template <typename T>
class Face{
    private:
        List<Point<T>> _points;
    public:
        DP_add_getter_name(List<Point<T>>, _points, Points)
        Face(){}
        Face(const List<Point<T>> & p):_points(p) {}
        inline void Add(const Point<T> & p){
            _points.push_back(p);
        }
        inline bool isFacial() const {
            if (_points.size() < 3)
                throw EXCEPTION("Count of point < 3");
            Point<T> p1 = DP::ElementAT(_points, 1);
            Point<T> p2 = DP::ElementAT(_points, 2);
            Point<T> p3 = DP::ElementAT(_points, 0);
            T aX = p1.GetX() - p3.GetX(), aY = p1.GetY() - p3.GetY(), bX = p2.GetX() - p3.GetX(), bY = p2.GetY() - p3.GetY();
            return (aY * bX - aX * bY < 0);
        }

        bool Contains (const Point<T> & p){
            for (auto x = _points.cbegin(); x!= _points.cend(); x++)
                if ((*x) == p)
                    return true;
            return false;
        }

        friend bool operator==(const Face& f1, const Face & f2){
            if (f1._points.size() != f2._points.size())
                return false;
            DP::UInt c=0;
            for (auto x1 = f1._points.cbegin(); x1 != f1._points.cend(); x1++)
                for (auto x2 = f2._points.cbegin(); x2 != f2._points.cend(); x2++)
                    if ((*x1) == (*x2)) {
                        c++;
                        break;
                    }
            return c == _points.size();
        }

        inline bool In(const Point<T> & p)const{
            Matrix<T> m =Matrix<T> (3, 3);
            Point<T> p1 = DP::ElementAT(_points, 0);
            Point<T> p2 = DP::ElementAT(_points, 1);
            Point<T> p3 = DP::ElementAT(_points, 2);

            m.Set(0, 0, p.GetX() - p1.GetX());
            m.Set(0, 1, p.GetY() - p1.GetY());
            m.Set(0, 2, p.GetZ() - p1.GetZ());

            m.Set(1, 0, p2.GetX() - p1.GetX());
            m.Set(1, 1, p2.GetY() - p1.GetY());
            m.Set(1, 2, p2.GetZ() - p1.GetZ());

            m.Set(2, 0, p3.GetX() - p1.GetX());
            m.Set(2, 1, p3.GetY() - p1.GetY());
            m.Set(2, 2, p3.GetZ() - p1.GetZ());

            return m.Det() == 0;
        }

};


using System;
using System.Collections.Generic;


    public class Face
    {
        private List<Point3d> _points;


        public void Println(){
            for (int i = 0; i < _points.Count; i++) {
                _points [i].Print ();
            }
            Console.WriteLine ();
        }
        public Point3d Normal(){
            Matrix m = new Matrix (3, 3);
            Point3d p1 = _points[0];
            Point3d p2 = _points[1];
            Point3d p3 = _points[2];

            m.Set (p2.x - p1.x, 1, 0);
            m.Set (p2.y - p1.y, 1, 1);
            m.Set (p2.z - p1.z, 1, 2);
            m.Set (p3.x - p1.x, 2, 0);
            m.Set (p3.y - p1.y, 2, 1);
            m.Set (p3.z - p1.z, 2, 2);

            // Почти уравнение плоскости
            var x = m.Get (1, 1) * m.Get (2, 2) - m.Get (1, 2) * m.Get (2, 1);
            var y = m.Get (1, 0) * m.Get (2, 2) - m.Get (1, 2) * m.Get (2, 0);
            var z = m.Get (1, 0) * m.Get (2, 1) - m.Get (1, 1) * m.Get (2, 0);

            Point3d res = new Point3d (x, y, z);
            return res;
        }

        private bool CheckInside(Point3d point1, Point3d point2, Point3d point3, int x, int y) {
            double fxyC, fxy;
            fxyC = point3.y * (point2.x - point1.x) - point3.x * (point2.y - point1.y) + point1.x * (point2.y - point1.y) - point1.y * (point2.x - point1.x);
            //fxyC = point3.Y * (point2.X - point1.X) - point3.X * (point2.Y - point1.Y) + point1.X * (point2.Y - point1.Y) - point1.Y * (point2.X - point1.X);
            //fxy =  y * (point2.X - point1.X) - x * (point2.Y - point1.Y) + point1.X * (point2.Y - point1.Y) - point1.Y * (point2.X - point1.X);
            fxy =  y * (point2.x - point1.x) - x * (point2.y - point1.y) + point1.x * (point2.y - point1.y) - point1.y * (point2.x - point1.x);
            if (((fxyC <= 0) && (fxy <= 0)) || ((fxyC >= 0) && (fxy >= 0)))
                return true;
            else
                return false;
        }
        //Subroutine to check any point(x,y) inside the triangle
        public bool Inside(int x, int y) {
            bool res = false;
            for (int i = 0; i < _points.Count; i++) {
                Point3d pt1 = _points[i % _points.Count];
                Point3d pt2 = _points[(i +1 )% _points.Count];
                Point3d pt3 = _points[(i +2 )% _points.Count];

                bool check = CheckInside(pt1, pt2, pt3, x, y) && CheckInside(pt2, pt3, pt1, x, y) && CheckInside(pt3, pt1, pt2, x, y);
                if (check == true)
                    res = true;
            }
            return res;
        }
        static public double MaxValue(){
            return 400;
        }
        public double DepthValue(int x,int y){
            double z = MaxValue ();
            for (int i = 0; i < _points.Count; i++) {
                Point3d pt1 = _points[(i)% _points.Count];
                Point3d pt2 = _points[(i + 1 )% _points.Count];
                Point3d pt3 = _points[(i + 2 )% _points.Count];

                Coefficient_Of_Plane surface;
                surface = new Coefficient_Of_Plane();
                surface.A = (pt2.z - pt3.z) * (pt1.y - pt2.y) - (pt1.z - pt2.z) * (pt2.y - pt3.y);
                surface.B = (pt2.x - pt3.x) * (pt1.z - pt2.z) - (pt1.x - pt2.x) * (pt2.z - pt3.z);
                surface.C = (pt2.y - pt3.y) * (pt1.x - pt2.x) - (pt1.y - pt2.y) * (pt2.x - pt3.x);
                surface.D = - pt1.x * (pt2.y * pt3.z - pt2.z * pt3.y) + pt1.y * (pt2.x * pt3.z - pt2.z * pt3.x) - pt1.z * (pt2.x * pt3.y - pt2.y * pt3.x);

                /*pt.A = (pt2.z - pt3.z) * (pt1.y - pt2.y) - (pt1.z - pt2.z) * (pt2.y - pt3.y);
                pt.B = (pt2.x - pt3.x) * (pt1.z - pt2.z) - (pt1.x - pt2.x) * (pt2.z - pt3.z);
                pt.C = (pt2.y - pt3.y) * (pt1.x - pt2.x) - (pt1.y - pt2.y) * (pt2.x - pt3.x);
                pt.D = - pt1.x * (pt2.y * pt3.z - pt2.z * pt3.y) + pt1.y * (pt2.x * pt3.z - pt2.z * pt3.x) - pt1.z * (pt2.x * pt3.y - pt2.y * pt3.x);

                /*surface.A = (pt3.z - pt2.z) * (pt1.y - pt2.y) - (pt2.z - pt1.z) * (pt2.y - pt3.y);
                surface.B = (pt2.x - pt3.x) * (pt2.z - pt1.z) - (pt1.x - pt2.x) * (pt3.z - pt2.z);
                surface.C = (pt2.y - pt3.y) * (pt1.x - pt2.x) - (pt1.y - pt2.y) * (pt2.x - pt3.x);
                surface.D = - pt1.x * (pt2.y * pt2.z - pt3.z * pt3.y) + pt1.y * (pt2.x * pt2.z - pt3.z * pt3.x) - pt1.z * (pt2.x * pt3.y - pt2.y * pt3.x);*/

                if (surface.B != 0)
                    z = (surface.A * x + surface.C * y + surface.D) / surface.B;
                else
                    z = (surface.A * x + surface.C * y + surface.D) / 0.001;
            }
            return z;
        }

    }
}


#endif
