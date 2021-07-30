#ifndef RESULTADO_H
#define RESULTADO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QEventTransition>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "controlador.h"
namespace Ui {
class Resultado;
}

class Resultado : public QMainWindow
{
    Q_OBJECT

public:
    explicit Resultado(QWidget *parent = nullptr);
    ~Resultado();

    void setControlador(Controlador *controlador);
    void generarHistograma();
private slots:
    void on_Genlibro_released();

    void on_GenHitory_released();

private:
    Ui::Resultado *ui;
    QPixmap m_barras;
    QPixmap m_histograma;
    void crearBarras();
    Controlador *m_controlador;
};

#endif // RESULTADO_H
