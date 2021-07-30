#ifndef CEDULA_H
#define CEDULA_H
#include <QMap>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSet>

class Cedula
{
public:
    Cedula();
    QMap<QString,QString> cedulas;
    QMap<QString,QString>::iterator i = cedulas.begin();
    QSet<QString> registro;
    QSet<QString>::iterator j = registro.begin();
    void ingresoVotantes();
    QStringList listacedula;
    QMap<QString,QString> m_delegado;
    QStringList getListacedula() const;

private:
    void agregarDelegado();

signals:

};

#endif // CEDULA_H
