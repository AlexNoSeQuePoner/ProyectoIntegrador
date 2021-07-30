#include "identificacion.h"
#include "ui_identificacion.h"

Identificacion::Identificacion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Identificacion)
{
    ui->setupUi(this);
    m_controlador = new Controlador();
    m_cedulas.ingresoVotantes();
}

Identificacion::~Identificacion()
{
    delete ui;
}
void Identificacion::on_Ingresar_clicked()
{
    if(verificar()){
        hide();
    }else {
        ui->inCedula->clear();
    }

}

Ui::Identificacion *Identificacion::getUi() const
{
    return ui;
}

void Identificacion::setControlador(Controlador *controlador)
{
    m_controlador = controlador;
}


bool Identificacion::aprobacion()
{
    QStringList horario;

    QFile f("Hora.txt");
    //creando fichero
    QTextStream in (&f);
    //mostramos un mensaje de adevertencia en caso de que no se pueda abrir el archivo
    if(!f.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"Hora","No se puede abrir el archivo Hora.txt");
        return false;
    }
    //guardamos en nuestro lista cedula
    while (!in.atEnd()) {
        //guardamos cada linea y separamos el numero de cedula del nombre del votante con ; asi sabra que cada vez que encuentre ; separa un elemento por linea
        horario<<(in.readLine().split(QLatin1Char(';')));
    }
    //insertamos los vatoates a nuestro mapa donde i es la cedula y key y la c es el nombre del botante
    time_t fecha =time(0);
    tm * date=localtime(&fecha);

    if(date->tm_hour>horario.at(1).toInt()){
        int horas=date->tm_hour-horario.at(1).toInt();
        QMessageBox::warning(this,"Aprobacion","Han pasado "+QString::number(horas)+" horas para ejercer el voto UnU");
        return false;
    }else if (date->tm_hour<horario.at(0).toInt()){
        int horas=horario.at(0).toInt()-date->tm_hour;
        QMessageBox::warning(this,"Aprobacion","Faltan "+QString::number(horas)+" horas para ejercer el voto UnU");
        return false;
    }else if (date->tm_mday<horario.at(2).toInt()){
        int dias=date->tm_mday-horario.at(2).toInt();
        QMessageBox::warning(this,"Aprobacion","Faltan "+QString::number(dias)+" dias para ejercer el voto UnU");
        return false;
    }else if (date->tm_mday>horario.at(3).toInt()){
        int dias=horario.at(3).toInt()-date->tm_mday;
        QMessageBox::warning(this,"Aprobacion","Han pasado "+QString::number(dias)+" dias para ejercer el voto UnU");
        return false;
    }else{
        return true;
    }
    return 0;
}

bool Identificacion::verificar()
{

    //Valida que el campo para ingresar la cedula no este vacio
    QString numcedula = ui->inCedula->text();
    m_controlador->setNumeroCedula(numcedula);
    if(ui->inCedula->text().isEmpty()){
        QMessageBox::warning(this,"Identificacion"," Porfavor ingrese su numero de cedula");
        return  false;
    }
    //Valida que el set contenga el dato ingresado en la interfaz
    else if((m_cedulas.m_delegado.contains(ui->inCedula->text()))&&(m_controlador->antesVoto())){
        Resultado *objResultado=new Resultado;
        objResultado->setControlador(m_controlador);
        objResultado->show();
        hide();
        return true;
    }
    else if(m_controlador->comprobarCedulaVoto(numcedula)){
        QMessageBox::warning(this,"Identificacion","Usted ya ha votado");
        return false;
    }
    else if(m_cedulas.cedulas.contains(ui->inCedula->text())){
        m_controlador->setAntesVoto(true);
        m_controlador->inCedulaSet();
        Votacion *objVotacion=new Votacion;
        objVotacion->setControlador(m_controlador);
        objVotacion->show();
        hide();
        return true;
    }else if(!m_controlador->antesVoto()){
        QMessageBox::critical(this,"Identificacion","Aun no se han registrado Votos");
        return false;
    }else{
        QMessageBox::critical(this,"Identificacion"," Usted no consta en el padron electoral");
        return false;
    }


    return 0;
}
