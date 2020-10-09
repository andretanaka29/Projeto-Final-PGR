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

private:
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

    QTimer *atualizar;

    Janela *janela1;

private slots:
    void atualizaEstado();

};
#endif // MAINWINDOW_H
