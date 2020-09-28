#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QUdpSocket>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;

    QPushButton *botaoSair;
    QPushButton *fecharJanela;
    QPushButton *abrirJanela;
    QLineEdit *estadoTempo;
    QLineEdit *estadoJanela;
    QLabel *comandoLabel;
    QLabel *estadoLabel;
    QLabel *timerLabel;
    QTimeEdit *relogio;
};
#endif // MAINWINDOW_H
