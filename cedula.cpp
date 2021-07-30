#include "cedula.h"


Cedula::Cedula()
{

}

void Cedula::ingresoVotantes(){

    QFile f("Padron.txt");
    //creando fichero
    QTextStream in (&f);
    //mostramos un mensaje de adevertencia en caso de que no se pueda abrir el archivo
    if(!f.open(QIODevice::ReadOnly)){
    }else {
        //guardamos en nuestro lista cedula
        while (!in.atEnd()) {
            //guardamos cada linea y separamos el numero de cedula del nombre del votante con ; asi sabra que cada vez que encuentre ; separa un elemento por linea

            listacedula<<(in.readLine().split(QLatin1Char(';')));

        }
        //insertamos los vatoates a nuestro mapa donde i es la cedula y key y la c es el nombre del votante
        for (int i=0;i<listacedula.size()-1;i=i+2) {
            int c=i+1;
            this->cedulas.insert(listacedula.at(i),listacedula.at(c));
        }
    f.close();
    }
    agregarDelegado();
}

QStringList Cedula::getListacedula() const
{
    return listacedula;
}

void Cedula::agregarDelegado()
{
    QStringList lDegelegado;
    QFile f("Delegado.txt");
    QTextStream in (&f);
    if(!f.open(QIODevice::ReadOnly)){
    }else {
        while (!in.atEnd()) {
           lDegelegado<<(in.readLine().split(QLatin1Char(';')));
        }
        for (int i=0;i<lDegelegado.size()-1;i=i+2) {
            int c=i+1;
            this->m_delegado.insert(lDegelegado.at(i),lDegelegado.at(c));
        }
    f.close();
    }
}

