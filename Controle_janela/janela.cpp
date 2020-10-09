#include "janela.h"
#include <QtNetwork>
#include <QtCore>


Janela::Janela(QObject *parent)
    : QObject(parent)
{
    udpSocket.bind(8888);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

    timer->start(2 * 1000);
}

QString Janela::tempo(char *dataArduino)
{
    QString _tempo;

    if(*dataArduino == 'U' || *dataArduino == 'T')
    {
        _tempo = "Está chovendo!";
    }
    else
    {
        _tempo = "Sem chuva!";
    }

    return _tempo;
}

QString Janela::estadoJanela(char *dataArduino)
{
    QString _estadoJanela;

    if(*dataArduino == 'U' || *dataArduino == 'E')
    {
        _estadoJanela = "Janela fechada!";
    }
    else
    {
        _estadoJanela = "Janela aberta!";
    }

    return _estadoJanela;
}

void Janela::comandoAbre()
{
    udpSocket.writeDatagram(QByteArray(1, 'a'), QHostAddress("192.168.0.177"), 8888);
}

void Janela::comandoFecha()
{
    udpSocket.writeDatagram(QByteArray(1, 'f'), QHostAddress("192.168.0.177"), 8888);
}

void Janela::processPendingDatagrams()
{
    QByteArray datagram;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    _clima = tempo(datagram.data());
    _janela = estadoJanela(datagram.data());

}

void Janela::sendDatagram()
{
    udpSocket.writeDatagram(QByteArray(1, 'e'), QHostAddress("192.168.0.177"), 8888);
}
