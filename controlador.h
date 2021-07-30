#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QQueue>
#include <ctime>
#include "cedula.h"
#include "votos.h"

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);
    QString numeroCedula() const;
    void setNumeroCedula(const QString &numeroCedula);
    QString nombreVotante();
    bool comprobarCedulaVoto(QString numeroCedula);
    void inCedulaSet();

    void votosArauz();
    void votosLasso();
    void votosBlancos();
    void votosNulos();

    int altura(int i);
    void calcularAltura(int valor, int total, int &resultado, int parametro);
    float porcentaje(int i);
    void calcularPorcentaje(int valor, int total, float &resultado, int parametro);
    bool antesVoto() const;
    QPixmap generarHistograma();
    void alturaBarrasH(int &altura1, int &altura2, int &altura3, int &altura4);

    void setAntesVoto(bool antesVoto);
private:
    Cedula m_cedula;
    QString m_numeroCedula;
    Votos m_voto;
    void guardarVotos(QString stringVotos);
    QString hora();
    bool m_antesVoto = false;
signals:

};

#endif // CONTROLADOR_H
