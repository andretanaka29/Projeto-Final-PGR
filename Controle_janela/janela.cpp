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

void Janela::tempo(char *dataArduino)
{
    if(*dataArduino == 'U' || *dataArduino == 'T')
    {
        _clima = "Está chovendo!";
    }
    else
    {
        _clima = "Sem chuva!";
    }

    //return _clima;
}

void Janela::estadoJanela(char *dataArduino)
{
    if(*dataArduino == 'U' || *dataArduino == 'E')
    {
        _janela = "Janela fechada!";
    }
    else
    {
        _janela = "Janela aberta!";
    }

    //return _janela;
}

char Janela::comandoAbre()
{
    return sendData = 'a';
}

char Janela::comandoFecha()
{
    return sendData = 'f';
}

void Janela::processPendingDatagrams()
{
    QByteArray datagram;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    tempo(datagram.data());
    estadoJanela(datagram.data());

}

void Janela::sendDatagram()
{
    udpSocket.writeDatagram(QByteArray(1, sendData), QHostAddress("192.168.0.177"), 8888);
}
