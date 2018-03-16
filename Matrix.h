#ifndef MATRIX
#define MATRIX

#include <DPLib.conf.h>
#include <Generator/CodeGenerator.h>
#include <Types/Exception.h>

using DP::UInt;

template <typename T>
class Matrix{
    private:
        T ** _matr;
        UInt m;
        UInt n;
    public:
        /// <param name="n"> Кол-во строк</param>
        /// <param name="m"> Кол-во столбцов</param>
        Matrix(UInt n, UInt m): m(m), n(n){
            _matr = new T*[m];
            for (UInt i = 0; i < m; i++){
                _matr[i] = new T [n];
                for (UInt j = 0; j < n; j++){
                    _matr[i][j] = 0;
                }
            }
        }
        ~Matrix(){
            /*for (UInt i = 0; i < m; i++)
                delete [] _matr[i];
            delete [] _matr;
            i=0;
            j=0;*/
        }

        //Кол-во строк
        DP_add_getter_name(UInt, m, M)
        //Кол-во столбцов
        DP_add_getter_name(UInt, n, N)

        template <typename Ostream>
        friend Ostream & operator << (Ostream & os, const Matrix & m){
            for (UInt i = 0; i < m.m; i++){
                for (UInt j = 0; j < m.n; j++){
                    os << m._matr[i][j] << " ";
                }
                os << "\n";
            }
            return os;
        }

        // Задать значение элементу значение
        /// <param name="val">Значение</param>
        /// <param name="i">Значение по  N (строка)</param>
        /// <param name="j">Значение по M (столбец)</param>
        inline void Set(UInt i, UInt j, const T & val){
            if (i > m || j > n)
                throw EXCEPTION("i > m || j > n");
            _matr[i][j] = val;
        }
        /// Получение значение элемента
        /// <param name="i">Значение по  N (строка)</param>
        /// <param name="j">Значение по M (столбец)</param>
        inline T Get(int i, int j)const{
            if (i > m || j > n)
                throw EXCEPTION("i > m || j > n");
            return _matr[i][j];
        }

        /// Перемножение матриц
        friend Matrix operator*(const Matrix & m1, const Matrix & m2){
            Matrix res = Matrix(m2.n, m1.m);
            for (UInt i = 0; i < m1.m; i++)
                for (UInt j = 0; j < m2.n; j++)
                    for (UInt k = 0; k < m2.m; k++)
                        res._matr[i][j] += m1._matr[i][k] * m2._matr[k][j];

            return res;
        }
        /*public Matrix Mult(Matrix m2) {
            Matrix res = new Matrix(m2._n, _m);

            for (int i = 0; i < _m; i++) {
                for (int j = 0; j < m2._n; j++) {
                    for (int k = 0; k < m2._m; k++) {
                        res._matr[i][j] += _matr[i][k] * m2._matr[k][j];
                    }
                }
            }

            return res;
        }*/
};

#endif // MATRIX

