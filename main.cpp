#include "identificacion.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Identificacion i;
    if(i.aprobacion()==false){
        i.close();
    }else {
        i.show();
    }


    return a.exec();
}
