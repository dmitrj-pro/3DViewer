#include "Viewer.h"
#include <QApplication>
#include <Types/Exception.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try{
        Viewer w;
        w.show();

        return a.exec();
    } catch (DP::LineException e){
        std::cout << e.toString() << "\n";
    } catch (DP::Exception e){
        std::cout << e.toString() << "\n";
    }
}
