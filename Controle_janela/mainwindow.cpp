#include "mainwindow.h"
#include <QtNetwork>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    janela1 = new Janela;
    alarme = new Alarme;

    botaoSair = new QPushButton(tr("Sair"));

    connect(botaoSair, SIGNAL(clicked()), this, SLOT(close()));

    fecharJanela = new QPushButton(tr("Fechar janela"));
    abrirJanela = new QPushButton(tr("Abrir janela"));

    connect(fecharJanela, SIGNAL(clicked()), janela1, SLOT(comandoFecha()));
    connect(abrirJanela, SIGNAL(clicked()), janela1, SLOT(comandoAbre()));

    ipEdit = new QLineEdit;
    ipLabel = new QLabel("IP:");

    connect(ipEdit, SIGNAL(textChanged(const QString &)),
                janela1, SLOT(ipJanela(const QString &)));

    estadoTempo = new QLineEdit;
    estadoJanela = new QLineEdit;

    estadoTempo->setReadOnly(true);
    estadoJanela->setReadOnly(true);

    relogio = new QTimeEdit;
    iniciaTimer = new QPushButton(tr("Inicia Timer"));

    connect(iniciaTimer, SIGNAL(clicked()), this, SLOT(ligaTimer()));
    connect(alarme, SIGNAL(tocaAlarme()), janela1, SLOT(comandoFecha()));

    estadoClimaLabel = new QLabel("Clima:");
    estadoJanelaLabel = new QLabel("Estado da Janela:");
    comandoLabel = new QLabel("Comandos");
    timerLabel = new QLabel("Timer");

    atualizar = new QTimer;
    connect(atualizar, SIGNAL(timeout()), this, SLOT(atualizaEstado()));
    atualizar->start(500);

    QHBoxLayout *topLineLayout = new QHBoxLayout;
    topLineLayout->addWidget(ipLabel);
    topLineLayout->addWidget(ipEdit);

    QVBoxLayout *topLeftLayout = new QVBoxLayout;
    topLeftLayout->addWidget(comandoLabel);
    topLeftLayout->addWidget(timerLabel);
    topLeftLayout->addWidget(relogio);
    topLeftLayout->addWidget(iniciaTimer);
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
    mainLayout->addLayout(topLineLayout);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Controle de janela"));
}

void MainWindow::atualizaEstado()
{
    estadoTempo->setText(janela1->_clima);
    estadoJanela->setText(janela1->_janela);
}

void MainWindow::ligaTimer()
{
    QTime horario = relogio->time();
    alarme->iniciaAlarme(horario);
}

MainWindow::~MainWindow()
{

}
