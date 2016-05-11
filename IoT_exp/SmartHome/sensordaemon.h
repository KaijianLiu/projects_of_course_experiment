#ifndef SENSORDAEMON_H
#define SENSORDAEMON_H
#include<QThread>
#include<Windows.h>

//Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

class SensorDaemon: public QThread
{
   Q_OBJECT
public:
    //constructor
    SensorDaemon(QObject *parent = 0);
    //to stop the thread
    void stop();
protected:
    //thread execute this method
    void run();
signals:
    //error occurred in transfer thread
    void nop(const QString &);
private:
    //init the two sockets
    void initSockets();
    //release resources
    void releaseSockets();
    //connect the inited sockets
    void connectSockets();
    volatile bool stopped;

    WSADATA wsad;//to init winsock
    SOCKET ServerSocket;//server socket to accept an client connection
    SOCKET ClientSocket;//client socket accepted
};

#endif // SENSORDAEMON_H

