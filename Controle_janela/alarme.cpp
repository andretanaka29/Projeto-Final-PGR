#include "alarme.h"
#include <QTime>

Alarme::Alarme(QObject *parent) : QObject(parent)
{

}

void Alarme::iniciaAlarme(QTime horario)
{
    *horarioAlarme = horario;
    QTimer *timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(comparaHorario()));
    timer->start(60*1000);
}

void Alarme::comparaHorario()
{
    QTime horarioAtual = QTime::currentTime();

    if(horarioAlarme->hour() == horarioAtual.hour()
            && horarioAlarme->minute() == horarioAtual.minute())
    {
        emit tocaAlarme();
    }
}
