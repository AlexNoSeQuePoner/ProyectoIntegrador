#include "controlador.h"


Controlador::Controlador(QObject *parent) : QObject(parent)
{

}


QString Controlador::numeroCedula() const
{
    return m_numeroCedula;
}

void Controlador::setNumeroCedula(const QString &numeroCedula)
{
    m_numeroCedula = numeroCedula;
}

QString Controlador::nombreVotante()
{
    m_cedula.ingresoVotantes();
    for (int i=0;i<m_cedula.listacedula.size()-1;i=i+2) {
        int x= i+1;
        if(m_numeroCedula==m_cedula.listacedula.at(i)){
            return m_cedula.listacedula.at(x);
        }
    }
    return "\0";
}

bool Controlador::comprobarCedulaVoto(QString numeroCedula)
{
    if(m_cedula.registro.contains(numeroCedula)){
        return true;
    }
    else if(m_cedula.registro.isEmpty()){
    m_cedula.registro.insert(m_numeroCedula);
    return false;
    }
    else{
    m_cedula.registro.insert(m_numeroCedula);
    return false;
    }
}

void Controlador::inCedulaSet()
{
    m_cedula.registro.insert(m_numeroCedula);
}

QString Controlador::hora()
{
    time_t fecha =time(0);
    tm * date=localtime(&fecha);
    int hora = date->tm_hour;
    m_voto.setVotosTiempo(hora);
    QString horas = QString::number(date->tm_hour);
    QString minutos = QString::number(date->tm_min);
    return horas+"h"+minutos;
}

void Controlador::setAntesVoto(bool antesVoto)
{
    m_antesVoto = antesVoto;
}

bool Controlador::antesVoto() const
{
    return m_antesVoto;
}

QPixmap Controlador::generarHistograma()
{
    QPixmap histograma;
    histograma = QPixmap(661, 441);
    histograma.fill(Qt::white);
    //crear pintor
    QPainter painter(&histograma);

    int x = 55;
    int y = 90;
    int ancho = 100;
    int votos7a10 = 0;
    int votos10a13 = 0;
    int votos13a16 = 0;
    int votos16a15 = 0;

    alturaBarrasH(votos7a10, votos10a13, votos13a16, votos16a15);
    int total = votos7a10 + votos10a13 + votos13a16 + votos16a15;

    int alto_1;
    int alto_2;
    int alto_3;
    int alto_4;
    calcularAltura(votos7a10, total, alto_1, 300);
    calcularAltura(votos10a13, total, alto_2, 300);
    calcularAltura(votos13a16, total, alto_3, 300);
    calcularAltura(votos16a15, total, alto_4, 300);
    QString strVotos;
    QPen pincel;
    pincel.setWidth(5);
    pincel.setJoinStyle(Qt::MiterJoin);

    QColor colorBorde(0,13,200);
    QColor colorRelleno(6,22,255);

    pincel.setColor(colorBorde);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno);
    painter.setPen(pincel);
    painter.drawRect(x, y+(300-alto_1), ancho, alto_1);
    painter.drawRect(x+150, y+(300-alto_2), ancho, alto_2);
    painter.drawRect(x+300, y+(300-alto_3), ancho, alto_3);
    painter.drawRect(x+450, y+(300-alto_4), ancho, alto_4);

    pincel.setColor(Qt::black);
    painter.setPen(pincel);
    painter.setFont(QFont("Arial", 14));

    painter.drawText(x, y+(320), "7h00 a 9h59");
    painter.drawText(x, y+(340), "Votos: " + strVotos.setNum(votos7a10));
    painter.drawText(x+150, y+(320), "10h00 a 12h59");
    painter.drawText(x+150, y+(340), "Votos: " + strVotos.setNum(votos10a13));
    painter.drawText(x+300, y+(320), "13h00 a 15h59");
    painter.drawText(x+300, y+(340), "Votos: " +strVotos.setNum(votos13a16));
    painter.drawText(x+450, y+(320), "16h00 a 17h00");
    painter.drawText(x+450, y+(340), "Votos: " + strVotos.setNum(votos16a15));

    painter.drawLine(x-20, y-50, x-20, y+300);
    painter.drawLine(x-20, y+300, 620 , y+300);
    return histograma;
}

void Controlador::alturaBarrasH(int &altura1, int &altura2, int &altura3, int &altura4)
{
    QQueue <int>  tempVotos = m_voto.votosTiempo();
    while (!tempVotos.empty()) {
        if((tempVotos.last() >= 7)&&(tempVotos.last() < 10)){
            ++altura1;
        } else if((tempVotos.last() >= 10)&&(tempVotos.last() < 13)){
            ++altura2;
        } else if((tempVotos.last() >= 13)&&(tempVotos.last() < 16)){
            ++altura3;
        }else if((tempVotos.last() >= 16)&&(tempVotos.last() < 17)){
            ++altura4;
        }
        tempVotos.pop_back();
    }
}

void Controlador::votosArauz()
{
    m_voto.aumentarVotoA();
    QString stringVotos = "Voto: Arauz; Hora: " + hora();
    guardarVotos(stringVotos);
}

void Controlador::votosLasso()
{
    m_voto.aumentarVotoL();
    QString stringVotos = "Voto: Lasso; Hora: " + hora();
    guardarVotos(stringVotos);
}

void Controlador::votosBlancos()
{
    m_voto.aumentarVotoB();
    QString stringVotos = "Voto: Blanco; Hora: " + hora();
    guardarVotos(stringVotos);
}

void Controlador::votosNulos()
{
    m_voto.aumentarVotoN();
    QString stringVotos = "Voto: Nulo; Hora: " + hora();
    guardarVotos(stringVotos);
}

int Controlador::altura(int i)
{
    int altura;
    int votosA = m_voto.votoA();
    int votosL = m_voto.votoL();
    int votosB = m_voto.votoB();
    int votosN = m_voto.votoN();
    int totalVotos = votosA + votosB + votosL + votosN;
    if (i == 1){
        calcularAltura(votosA, totalVotos, altura, 300);
        return altura;
    }else if (i == 2){
        calcularAltura(votosL, totalVotos, altura, 300);
        return altura;
    }else if(i == 4){
        calcularAltura(votosB, totalVotos, altura, 300);
        return altura;
    }else if(i == 3){
        calcularAltura(votosN, totalVotos, altura, 300);
        return altura;
    }
    return 0;
}

void Controlador::calcularAltura(int valor, int total, int &resultado, int parametro)
{
    resultado = (valor * parametro) / total;
}

float Controlador::porcentaje(int i)
{
    float porcentaje;
    int votosA = m_voto.votoA();
    int votosL = m_voto.votoL();
    int votosB = m_voto.votoB();
    int votosN = m_voto.votoN();
    int totalVotos = votosA + votosB + votosL + votosN;
    if (i == 1){
        calcularPorcentaje(votosA, totalVotos, porcentaje, 100);
        return porcentaje;
    }else if (i == 2){
        calcularPorcentaje(votosL, totalVotos, porcentaje, 100);
        return porcentaje;
    }else if(i == 4){
        calcularPorcentaje(votosB, totalVotos, porcentaje, 100);
        return porcentaje;
    }else if(i == 3){
        calcularPorcentaje(votosN, totalVotos, porcentaje, 100);
        return porcentaje;
    }
    return 0;
}

void Controlador::calcularPorcentaje(int valor, int total, float &resultado, int parametro)
{
    resultado = (valor * parametro) / total;
}

void Controlador::guardarVotos(QString stringVotos)
{
    QFile file("votos.txt");
    QTextStream out(&file);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Append)){
        file.open(QIODevice::WriteOnly);
        out<<stringVotos + "\n**************************************\n";
    }else{
        out<<stringVotos + "\n**************************************\n";
    }
    file.close();
}


