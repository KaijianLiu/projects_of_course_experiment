#include "sensordaemon.h"



SensorDaemon::SensorDaemon(QObject *parent) :QThread(parent)
{
    stopped = false;
}

void SensorDaemon::run(){
    initSockets();		//init sockets
    connectSockets();	//connect the sockets
/*    while (!stopped){
        //critical section
        fullSem.acquire();//down
        Message msg = msgQueue[qhead];
        qhead = (qhead + 1) % RF_MESSAGE_QUEUE_LENGTH;
        emptySem.release();//up
        //hostByteOrder2NetByteOrder(msg);

        //send an Msg struct in three part  in case of packet losing
        int retVal		= send(glassSocket, (char*)msg.left_hand, sizeof(msg.left_hand), 0);
            retVal		= send(glassSocket, (char*)msg.right_hand, sizeof(msg.right_hand), 0);
            retVal		= send(glassSocket, (char*)(&msg.left), 10, 0);
        if (SOCKET_ERROR == retVal){
                break;
        }
        Sleep(33);
    }
*/
    stopped = true;
    releaseSockets();
}
void SensorDaemon::stop(){
    stopped = true;
}
void SensorDaemon::initSockets(){
 /*   stopped = false;
    if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0){
       // QString s("[Transfer thread] WSAStartup(MAKEWORD(2, 2), &wsad) failed!");
       // emit TransferErrorOccurred(s);
        stopped = true;
        return;
    }
    //create server socket
    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ServerSocket == INVALID_SOCKET) {
       // QString s("[Transfer thread] ServerSocket == INVALID_SOCKET");
       // emit TransferErrorOccurred(s);
        stopped = true;
        return;
    }
    SOCKADDR_IN addrServ;
    //server socket address
    addrServ.sin_family = AF_INET;
    addrServ.sin_port = htons(GLASS_SERVER_PORT);
    addrServ.sin_addr.s_addr = INADDR_ANY;
    //bind socket
    int retVal = bind(ServerSocket, (LPSOCKADDR)&addrServ, sizeof(SOCKADDR_IN));
    if (SOCKET_ERROR == retVal){
        QString s("[Transfer thread] bind(ServerSocket, (LPSOCKADDR)&addrServ... failed");
        emit TransferErrorOccurred(s);
        stopped = true;
        return;
    }
    //start listen
    retVal = listen(ServerSocket,1);
    if (SOCKET_ERROR == retVal){
        QString s("[Transfer thread] listen(ServerSocket,1) failed");
        emit TransferErrorOccurred(s);
        stopped = true;
        return;
    }
  */   //create control socket
    //	controlSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //	if (INVALID_SOCKET == controlSocket)/*error*/;

}

void SensorDaemon::connectSockets(){
/*
    SOCKADDR_IN addrClient;
    int addClientLen = sizeof(addrClient);
    //blocked until a client conected
    glassSocket = accept(ServerSocket, (sockaddr FAR*)&addrClient, &addClientLen);
    if (glassSocket == INVALID_SOCKET){
        QString s("[Transfer thread] accept(ServerSocket,... failed");
        emit TransferErrorOccurred(s);
        stopped = true;
        return;
     }
*/
}

void SensorDaemon::releaseSockets(){
    closesocket(ServerSocket);
    closesocket(ClientSocket);
    WSACleanup();
}

