#include "certificado.h"
#include "ui_certificado.h"


Certificado::Certificado(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Certificado)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
    fecha();
    m_carnet = QPixmap(502, 325);
}

Certificado::~Certificado()
{
    delete ui;

}
void Certificado::fecha()
{
    time_t fecha =time(0);
    tm * date=localtime(&fecha);
    QString horas = QString::number(date->tm_hour);
    QString minutos = QString::number(date->tm_min);
     m_hora= horas+"h"+minutos;
    QString dia = QString::number(date->tm_mday);
    QString mes = QString::number(date->tm_mon+1);
    QString year = QString::number(date->tm_year+1900);
    m_fecha = dia+"/"+mes+"/"+year;
}

void Certificado::crearCertificado()
{

    //Rellenar lienzo
    m_nombre=m_controlador->nombreVotante();
    m_cedula = m_controlador->numeroCedula();
    m_carnet.fill(Qt::white);
    QPainter painter(&m_carnet);
    painter.drawPixmap(25, 60, 115, 143, QString(QDir::currentPath() + "/Foto.jpg"));
    painter.setFont(QFont("Arial", 16));
    painter.drawText(160, 25, "Certificado de Votación");
    painter.drawText(160, 50, "Elecciones 2021");
    painter.setFont(QFont("Arial", 14));
    painter.drawText(155, 130, "Nombre: " + m_nombre);
    painter.drawText(155, 160, "Cédula: " + m_cedula);
    painter.drawText(155, 190, "Fecha: " + m_fecha);
    painter.drawText(155, 220, "Hora: " + m_hora);
     ui->outCertificado->setPixmap(m_carnet);
}

void Certificado::setControlador(Controlador *controlador)
{
    m_controlador = controlador;
    crearCertificado();
    ui->outCertificado->setPixmap(m_carnet);
}

void Certificado::on_cmdGuardar_released()
{
    QDir directorio = QDir::home();
    QString pathArchivo = directorio.absolutePath() + "/Certificado.png";
    //Abrir un cuadro de dialogo para seleccionar el nombre y ubicacion del archivo
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar Imagen",
                                                   pathArchivo,
                                                    "Imagen(*.png)");
    if (!fileName.isEmpty())
    {
      m_carnet.save(fileName);
    }
    Identificacion *objIdentificacion = new Identificacion();
    objIdentificacion->setControlador(m_controlador);
    objIdentificacion->show();
    this->hide();
}




