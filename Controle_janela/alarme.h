#ifndef ALARME_H
#define ALARME_H

#include <QObject>
#include <QTimer>

class Alarme : public QObject
{
    Q_OBJECT
public:
    Alarme(QObject *parent = nullptr);

    void iniciaAlarme(QTime horario);

private:
    QTimer *timer;
    QTime *horarioAlarme;

private slots:
    void comparaHorario();

signals:
    void tocaAlarme();

};

#endif // ALARME_H
