#include "resultado.h"
#include "ui_resultado.h"
Resultado::Resultado(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Resultado)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
    m_barras = QPixmap(661, 441);
    m_histograma = QPixmap(661, 441);
}

Resultado::~Resultado()
{
    delete ui;
}

void Resultado::crearBarras()
{
    //Rellenar lienzo
    m_barras.fill(Qt::white);
    //crear pintor
    QPainter painter(&m_barras);

    int x = 55;
    int y = 90;
    int ancho = 100;
    float porcentaje_1 = m_controlador->porcentaje(1);
    float porcentaje_2 = m_controlador->porcentaje(2);
    float porcentaje_3 = m_controlador->porcentaje(3);
    float porcentaje_4 = m_controlador->porcentaje(4);
    int alto_1 = m_controlador->altura(1);
    int alto_2= m_controlador->altura(2);
    int alto_3 = m_controlador->altura(3);
    int alto_4 = m_controlador->altura(4);
    QString strPorcent;
    QPen pincel;
    pincel.setWidth(5);
    pincel.setJoinStyle(Qt::MiterJoin);

    QColor colorBorde(238,143,0);
    QColor colorRelleno(255,167,33);

    pincel.setColor(colorBorde);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno);
    painter.setPen(pincel);
    painter.drawRect(x, y+(300-alto_1), ancho, alto_1);

    QColor colorBorde2(0,13,200);
    QColor colorRelleno2(6,22,255);

    pincel.setColor(colorBorde2);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno2);
    painter.drawRect(x+150, y+(300-alto_2), ancho, alto_2);

    QColor colorRelleno3(0, 255, 125);
    QColor colorBorde3(0, 204, 102);

    pincel.setColor(colorBorde3);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno3);
    painter.drawRect(x+300, y+(300-alto_3), ancho, alto_3);

    QColor colorRelleno4(224, 224, 224);
    QColor colorBorde4(128, 128, 128);

    pincel.setColor(colorBorde4);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno4);
    painter.drawRect(x+450, y+(300-alto_4), ancho, alto_4);

    pincel.setColor(Qt::black);
    painter.setPen(pincel);
    painter.setFont(QFont("Arial", 14));

    painter.drawText(x, y+(260-alto_1), "Arauz");
    painter.drawText(x, y+(280-alto_1), "Lista 1  " + strPorcent.setNum(porcentaje_1) + "%");
    painter.drawText(x+150, y+(260-alto_2), "Lasso");
    painter.drawText(x+150, y+(280-alto_2), "Lista 2  " + strPorcent.setNum(porcentaje_2)+ "%");
    painter.drawText(x+300, y+(260-alto_3), "Nulos");
    painter.drawText(x+300, y+(280-alto_3), strPorcent.setNum(porcentaje_3) + "%");
    painter.drawText(x+450, y+(260-alto_4), "Blancos");
    painter.drawText(x+450, y+(280-alto_4), strPorcent.setNum(porcentaje_4) + "%");

    painter.drawLine(x-20, y-50, x-20, y+300);
    painter.drawLine(x-20, y+300, 620 , y+300);

    //mostrar el lienzo en el "cuadro"

    ui->outResultados->setPixmap(m_barras);

}

void Resultado::setControlador(Controlador *controlador)
{
    m_controlador = controlador;
    crearBarras();
}

void Resultado::generarHistograma()
{
    m_histograma = m_controlador->generarHistograma();
}

void Resultado::on_Genlibro_released()
{
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath() + "/Resultados.png";
    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar Imagen",
                                                   pathArchivo,
                                                    "Imagen(*.png)");
    if (!fileName.isEmpty())
    {
      m_barras.save(fileName);
    }
}

void Resultado::on_GenHitory_released()
{
    generarHistograma();
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath() + "/Histograma.png";
    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar Imagen",
                                                   pathArchivo,
                                                    "Imagen(*.png)");
    if (!fileName.isEmpty())
    {
      m_histograma.save(fileName);
    }
}
