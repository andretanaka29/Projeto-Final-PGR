#include "mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    udpSocket.bind(8888);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));

    botaoSair = new QPushButton(tr("Sair"));

    connect(botaoSair, SIGNAL(clicked()), this, SLOT(close()));

    fecharJanela = new QPushButton(tr("Fechar janela"));
    abrirJanela = new QPushButton(tr("Abrir janela"));

    estadoTempo = new QLineEdit;
    estadoJanela = new QLineEdit;

    estadoTempo->setReadOnly(true);
    estadoJanela->setReadOnly(true);

    relogio = new QTimeEdit;

    estadoLabel = new QLabel("Estado da Janela");
    comandoLabel = new QLabel("Comandos");
    timerLabel = new QLabel("Timer");

    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(comandoLabel);
    topLeftLayout->addWidget(timerLabel);
    topLeftLayout->addWidget(relogio);
    topLeftLayout->addWidget(fecharJanela);
    topLeftLayout->addWidget(abrirJanela);

    QVBoxLayout *topRightLayout = new QVBoxLayout;
    topRightLayout->addWidget(estadoLabel);
    topRightLayout->addWidget(estadoTempo);
    topRightLayout->addWidget(estadoJanela);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(topLeftLayout);
    topLayout->addLayout(topRightLayout);

    QVBoxLayout *bottomLayout = new QVBoxLayout;
    bottomLayout->addWidget(botaoSair);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Controle de janela"));
}

void MainWindow::processPendingDatagrams()
{
    QByteArray datagram;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    QString data;

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    in >> data;

    estadoTempo->setText(data);
    estadoJanela->setText(tr("Aberta"));
}

MainWindow::~MainWindow()
{

}

