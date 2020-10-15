#include "alarme.h"

Alarme::Alarme(QObject *parent) : QObject(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(comparaHorario()));
    timer.start(60*1000);
}

void Alarme::iniciaAlarme(QTime horario)
{
    horarioAlarme = horario;
}

void Alarme::comparaHorario()
{
    QTime horarioAtual = QTime::currentTime();

    if(horarioAlarme.hour() == horarioAtual.hour()
            && horarioAlarme.minute() == horarioAtual.minute())
    {
        emit tocaAlarme();
    }
}
