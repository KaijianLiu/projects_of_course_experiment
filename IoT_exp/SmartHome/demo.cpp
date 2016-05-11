#include"def.h"

#include<Windows.h>

//Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

void demo(){

    UART_PACKET(30) pkt;
    INIT_PKT(pkt, 30);
    for(int i=0;i<30;i++){
        pkt.data[i]=i;
    }
    CAL_CRC(pkt, 30);

    dump(&pkt, 30);

    UART_COMMAND(3) cmd;
    INIT_CMD(cmd, 3);
    cmd.data[0]=1;
    cmd.data[1]=2;
    cmd.data[2]=3;
    CAL_CRC(cmd, 3);

    dump(&cmd, 3);

}
#include<iostream>

using namespace std;
void socket_test(){
    WSADATA wsad;//to init winsock
    SOCKET ClientSocket;//client socket accepted
    SOCKADDR_IN addrSrv;
    if (WSAStartup(MAKEWORD(2, 2), &wsad) != 0){
        cout<<"WSAStartup"<<endl;
        return;
    }
    ClientSocket=socket(AF_INET,SOCK_STREAM,0);                    //创建socket
    addrSrv.sin_addr.S_un.S_addr=inet_addr("192.168.1.20");
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(5000);
    int res = connect(ClientSocket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
    if(res == SOCKET_ERROR){
        cout<<"error : connect(Cli... "<<res<<endl;
        exit(0);
    }else{
          cout<<"ok : connect(Cli..."<<endl;
    }

        UART_COMMAND(2) cmd;
        INIT_CMD(cmd,2);
        cmd.data[0] = 0x01;
        cmd.data[1] = 0x01;
       // cmd.data[2] = 0x00;
        CAL_CRC(cmd,2);
       //dump(&cmd,3);
        res = send(ClientSocket,(char *)&cmd,sizeof(cmd)+1,0);
        UART_PACKET(14) pkt;
        INIT_PKT(pkt,14);
        res = recv(ClientSocket,(char *)&pkt,sizeof(pkt),0);
        if(!res){
             cout<<"error : recv(Cli..."<<endl;
        }else{
             cout<<"ok : recv(Cli..."<<endl;
        }
        cout<<"pkt"<<endl;
        dump(&pkt,14);
        cout<<"pkt"<<endl<<endl<<endl;
        int a = 10;
        while(a-- > 0){
            UART_PACKET(3) pkt2;
            res = recv(ClientSocket,(char *)&pkt2,sizeof(pkt2),0);

            cout<<"pkt2:"<<endl;
            dump(&pkt2,3);
}
     cout<<"finish"<<endl;
     closesocket(ClientSocket);
     WSACleanup();
}





