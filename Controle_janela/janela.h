#ifndef JANELA_H
#define JANELA_H

#include <QString>
#include <QtWidgets>
#include <QUdpSocket>
#include <QTimer>

class Janela : public QWidget
{

    public:
        Janela(){};
        QString tempo(char *dataArduino);
        QString estadoJanela(char *dataArduino);

    private:
        QString _clima;
        QString _janela;

};

#endif // JANELA_H
