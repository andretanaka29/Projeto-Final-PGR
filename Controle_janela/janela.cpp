#include "janela.h"
#include <QtCore>

QString Janela::tempo(char *dataArduino)
{
    if(*dataArduino == 'U' || *dataArduino == 'T')
    {
        _clima = "Está chovendo!";
    }
    else
    {
        _clima = "Sem chuva!";
    }

    return _clima;
}

QString Janela::estadoJanela(char *dataArduino)
{
    if(*dataArduino == 'U' || *dataArduino == 'E')
    {
        _janela = "Janela fechada!";
    }
    else
    {
        _janela = "Janela aberta!";
    }

    return _janela;
}
