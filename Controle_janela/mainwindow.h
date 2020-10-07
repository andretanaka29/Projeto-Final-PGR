#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QUdpSocket>
#include <QTimer>
#include "janela.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void processPendingDatagrams();
    void sendDatagram();
    char comandoAbre();
    char comandoFecha();

private:
    QUdpSocket udpSocket;

    QPushButton *botaoSair;
    QPushButton *fecharJanela;
    QPushButton *abrirJanela;

    QLineEdit *estadoTempo;
    QLineEdit *estadoJanela;

    QLabel *comandoLabel;
    QLabel *estadoJanelaLabel;
    QLabel *estadoClimaLabel;
    QLabel *timerLabel;

    QTimeEdit *relogio;
    QTimer *timer;

    Janela *janela1;
    char sendData1;

};
#endif // MAINWINDOW_H
