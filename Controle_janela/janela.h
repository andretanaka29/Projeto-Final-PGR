#ifndef JANELA_H
#define JANELA_H

#include <QString>

class Janela
{
    public:
        Janela(){};
        QString tempo(bool sensorChuva);
        QString estadoJanela(bool sensorJanela);

    private:
        QString _clima;
        QString _janela;

};

#endif // JANELA_H
