#include "votos.h"

Votos::Votos(QObject *parent) : QObject(parent)
{
    m_votoA = 0;
    m_votoL = 0;
    m_votoN = 0;
    m_votoB = 0;
}


void Votos::setVotosTiempo(const int &votosTiempo)
{
    m_votosTiempo.append(votosTiempo);
}

int Votos::votoA() const
{
    return m_votoA;
}

void Votos::aumentarVotoA()
{
    ++m_votoA;
}

int Votos::votoL() const
{
    return m_votoL;
}

void Votos::aumentarVotoL()
{
    ++m_votoL;
}

int Votos::votoN() const
{
    return m_votoN;
}

void Votos::aumentarVotoN()
{
    ++m_votoN;
}

int Votos::votoB() const
{
    return m_votoB;
}

void Votos::aumentarVotoB()
{
    ++m_votoB;
}

QQueue<int> Votos::votosTiempo() const
{
    return m_votosTiempo;
}
