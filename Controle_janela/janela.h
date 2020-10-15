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

    QString _clima;
    QString _janela;

public slots:
    void ipJanela(const QString &text);
    void comandoAbre();
    void comandoFecha();
    void sendDatagram();
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;
    QTimer *timer;

    QString tempo(char *dataArduino);
    QString estadoJanela(char *dataArduino);
    QString ip_janela;

};

#endif // JANELA_H
