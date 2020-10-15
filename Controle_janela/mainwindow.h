#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QUdpSocket>
#include <QTimer>
#include <QLineEdit>
#include "janela.h"
#include "alarme.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *botaoSair;
    QPushButton *fecharJanela;
    QPushButton *abrirJanela;
    QPushButton *iniciaTimer;

    QLineEdit *ipEdit;
    QLineEdit *estadoTempo;
    QLineEdit *estadoJanela;

    QLabel *comandoLabel;
    QLabel *estadoJanelaLabel;
    QLabel *estadoClimaLabel;
    QLabel *timerLabel;
    QLabel *ipLabel;

    QTimeEdit *relogio;

    QTimer *atualizar;

    Janela *janela1;
    Alarme *alarme;

private slots:
    void atualizaEstado();
    void ligaTimer();

};
#endif // MAINWINDOW_H
