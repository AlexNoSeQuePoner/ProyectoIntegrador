#ifndef VOTOS_H
#define VOTOS_H

#include <QObject>
#include <QQueue>
#include <QString>
class Votos : public QObject
{
    Q_OBJECT
public:
    explicit Votos(QObject *parent = nullptr);

    void setVotosTiempo(const int &votosTiempo);

    int votoA() const;
    void aumentarVotoA();

    int votoL() const;
    void aumentarVotoL();

    int votoN() const;
    void aumentarVotoN();

    int votoB() const;
    void aumentarVotoB();

    QQueue<int> votosTiempo() const;

private:
    int m_votoA;
    int m_votoL;
    int m_votoN;
    int m_votoB;
    QQueue <int> m_votosTiempo;
signals:

};

#endif // VOTOS_H
