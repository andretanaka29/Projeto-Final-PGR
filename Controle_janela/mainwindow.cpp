#include "mainwindow.h"
#include <QtNetwork>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    janela1 = new Janela;
    udpSocket.bind(8888);

    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(sendDatagram()));

    timer->start(2 * 1000);

    botaoSair = new QPushButton(tr("Sair"));

    connect(botaoSair, SIGNAL(clicked()), this, SLOT(close()));

    fecharJanela = new QPushButton(tr("Fechar janela"));
    abrirJanela = new QPushButton(tr("Abrir janela"));

    connect(fecharJanela, SIGNAL(clicked()), this, SLOT(comandoFecha()));
    connect(abrirJanela, SIGNAL(clicked()), this, SLOT(comandoAbre()));

    estadoTempo = new QLineEdit;
    estadoJanela = new QLineEdit;

    estadoTempo->setReadOnly(true);
    estadoJanela->setReadOnly(true);

    relogio = new QTimeEdit;

    estadoClimaLabel = new QLabel("Clima:");
    estadoJanelaLabel = new QLabel("Estado da Janela:");
    comandoLabel = new QLabel("Comandos");
    timerLabel = new QLabel("Timer");

    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(comandoLabel);
    topLeftLayout->addWidget(timerLabel);
    topLeftLayout->addWidget(relogio);
    topLeftLayout->addWidget(fecharJanela);
    topLeftLayout->addWidget(abrirJanela);

    QVBoxLayout *topRightLayout = new QVBoxLayout;
    topRightLayout->addWidget(estadoClimaLabel);
    topRightLayout->addWidget(estadoTempo);
    topRightLayout->addWidget(estadoJanelaLabel);
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
    bool data1;
    bool data2;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    in >> data1 >> data2;

    estadoTempo->setText(janela1->tempo(data1));
    estadoJanela->setText(janela1->estadoJanela(data2));
}

void MainWindow::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out << sendData1 << sendData2;

    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, 8888);
}

bool MainWindow::comandoAbre()
{
    return sendData2 = 0;
}

bool MainWindow::comandoFecha()
{
    return sendData2 = 1;
}

MainWindow::~MainWindow()
{

}
