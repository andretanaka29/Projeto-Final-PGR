#ifndef JANELA_H
#define JANELA_H

#include <QString>
#include <QtWidgets>
#include <QUdpSocket>
#include <QTimer>
#include <QObject>

class Janela : public QObject
{
    Q_OBJECT

public:
    Janela(QObject *parent = 0);

    char sendData;
    QString _clima;
    QString _janela;

public slots:
    char comandoAbre();
    char comandoFecha();
    void sendDatagram();
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;
    QTimer *timer;


    void tempo(char *dataArduino);
    void estadoJanela(char *dataArduino);

};

#endif // JANELA_H
