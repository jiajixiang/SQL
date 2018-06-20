#ifndef INFORMATION_H
#define INFORMATION_H

#include"head.h"

class information
{
public:
    information();
    QString getName();
    QString getIP();
    QString getMac();
private:
    QString localHost;
    QString localIP;
    QString localMAC;
};

#endif // INFORMATION_H
