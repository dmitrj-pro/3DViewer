#ifndef FIGURE2
#define FIGURE2

#include <DPLib.conf.h>
#include <Generator/CodeGenerator.h>

using DP::List;

template <typename T>
class Figure2{
    private:
        Li
};


#endif // FIGURE2



using System;
using System.Collections.Generic;

namespace Render
{
    public class Figure2
    {
        public List<Face> _faces;

        public Figure2 (){
            _faces = new List<Face> ();
        }
        public void Add(Face f){
            _faces.Add (f);
        }
        public List<Face> Faces(){
            return _faces;
        }
        public Figure2 DeleteDoublicete(){
            Figure2 res = this;
            for (int i = 0; i < res._faces.Count; i++) {
                for (int j = i + 1; j < res._faces.Count; j++) {
                    if (res._faces [i].Equal (res._faces [j])) {
                        res._faces.RemoveAt (j);
                        j--;
                    }
                }
            }
            return res;
        }
        public void Print(){
            for (int i = 0; i< _faces.Count; i++) {
                _faces [i].Println ();
            }
        }

    }
}


