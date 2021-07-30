#ifndef CERTIFICADO_H
#define CERTIFICADO_H

#include <QMainWindow>
#include <ctime>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include "identificacion.h"
#include "controlador.h"
#include "cedula.h"
namespace Ui {
class Certificado;
}

class Certificado : public QMainWindow
{
    Q_OBJECT

public:
    explicit Certificado(QWidget *parent = nullptr);
    ~Certificado();   
    void setControlador(Controlador *controlador);

private slots:
    void on_cmdGuardar_released();
private:
    Ui::Certificado *ui;
    void certificar();
    void fecha();
    QString m_nombre;
    QString m_cedula;
    QString m_hora;
    QString m_fecha;
    QPixmap m_carnet;
    void crearCertificado();
    Controlador *m_controlador;

};

#endif // CERTIFICADO_H
