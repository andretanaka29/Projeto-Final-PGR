#include "janela.h"

QString Janela::tempo(bool sensorChuva)
{
    if(sensorChuva)
    {
        _clima = "Está chovendo!";
    }
    else
    {
        _clima = "Sem chuva!";
    }

    return _clima;
}

QString Janela::estadoJanela(bool sensorJanela)
{
    if(sensorJanela)
    {
        _janela = "Janela fechada!";
    }
    else
    {
        _janela = "Janela aberta!";
    }

    return _janela;
}
