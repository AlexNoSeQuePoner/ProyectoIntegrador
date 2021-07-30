#include "votacion.h"
#include "ui_votacion.h"


Votacion::Votacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Votacion)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
}

Votacion::~Votacion()
{
    delete ui;
}

void Votacion::Sufragio()
{
    if(ui->inVotoArauz->isChecked() && ui->inVotoLazzo->isChecked()){
        m_controlador->votosNulos();
    }else if(ui->inVotoArauz->isChecked() && !ui->inVotoLazzo->isChecked()){
        m_controlador->votosArauz();
    }else if(ui->inVotoLazzo->isChecked() && !ui->inVotoArauz->isChecked()){
        m_controlador->votosLasso();
    }else{
        m_controlador->votosBlancos();
    }
}

void Votacion::on_inVoto_clicked()
{
    Certificado *objCertificado = new Certificado();
    Sufragio();
    objCertificado->setControlador(m_controlador);
    hide();
    objCertificado->show();

}

void Votacion::setControlador(Controlador *controlador)
{
    m_controlador = controlador;
}
