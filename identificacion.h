#ifndef IDENTIFICACION_H
#define IDENTIFICACION_H

#include <QMainWindow>
#include "votacion.h"
#include "resultado.h"
#include "cedula.h"
#include "controlador.h"

namespace Ui {
class Identificacion;
}

class Identificacion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Identificacion(QWidget *parent = nullptr);
    ~Identificacion();
    bool aprobacion();
    bool verificar();
    Ui::Identificacion *getUi() const;
    void setControlador(Controlador *controlador);

private slots:

    void on_Ingresar_clicked();

private:
    Ui::Identificacion *ui;
    Cedula m_cedulas;
    Controlador *m_controlador;

};

#endif // IDENTIFICACION_H
