#ifndef VOTACION_H
#define VOTACION_H

#include <QMainWindow>
#include "certificado.h"
#include <QQueue>
#include "identificacion.h"
#include "controlador.h"
#include "cedula.h"

namespace Ui {
class Votacion;
}

class Votacion : public QMainWindow
{
    Q_OBJECT   
public:
    explicit Votacion(QWidget *parent = nullptr);
    ~Votacion();
    void Sufragio();
    void setControlador(Controlador *controlador);

private slots:
    void on_inVoto_clicked();

private:
    Ui::Votacion *ui;
    Controlador *m_controlador;
};

#endif // VOTACION_H
