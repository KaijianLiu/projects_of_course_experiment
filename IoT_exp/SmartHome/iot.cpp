
#include <stdio.h>
#include <Windows.h>

#pragma comment(lib,"WS2_32.lib")

typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef uint8   byte;
typedef struct _UART_COMMAND
{
    uint8 head1;				//0xaa
    uint8 head2;				//0x44

    uint8 type;				//上下行数据标识
    uint8 dest[8];				//目的地址
    uint8 src[8];				//源地址
    uint8 sn;				//数据包序号
    uint8 len[2];			        //len[0]存放高字节，len[1]存放低字节，len指示负载长度
    uint8 Pkt_Type;				//数据包类型
    uint8 Reserved;			        //冗余位
    uint8 data[3];		        //数据指针
   // byte  *data    ;       //2012-03-28  修改为指针 支持带不确定参数的实验箱协议
    uint8 crc[2];				//CRC16算法数据
    } UART_COMMAND;



static uint16 myCRC16(unsigned char* data,uint16 len)
{
    uint16 crcsum=0;
    uint16 *p=(uint16*)data;
    while (len> 1)
    {
        crcsum^=*p++;
        len -=2;
    }
    if (len)
    {
        crcsum^= *(uint8 *)p;
    }
    return crcsum;
}


int mainqq()
{
    WSADATA wsd;
    SOCKET sockClient;                                            //客户端socket
    SOCKADDR_IN addrSrv;
    char recvBuf[100];
    if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
    {
        printf("start up failed!\n");
        return 0;
    }else{
         printf("staeeeeeeeeeeeeeeeeeeeeeed!\n");
    }
    sockClient=socket(AF_INET,SOCK_STREAM,0);                    //创建socket
    addrSrv.sin_addr.S_un.S_addr=inet_addr("192.168.1.20");
    addrSrv.sin_family=AF_INET;
    addrSrv.sin_port=htons(5000);
    connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));    //连接服务器端
   // recv(sockClient,recvBuf,100,0);                                //接收服务器端数据
    printf("ss\n");




    uint8  crcnum,crcnum2;
    uint16 mycrcnum;   //校验值
    byte buffer[100];

    buffer[0] = 0xaa; //head1
    buffer[1] = 0x44;//head2
    buffer[2] = 0x02;//type
    //dest
    buffer[3] = 0xff;
    buffer[4] = 0xff;
    buffer[5] = 0xff;
    buffer[6] = 0xff;
    buffer[7] = 0xff;
    buffer[8] = 0xff;
    buffer[9] = 0xff;
    buffer[10] = 0xff;
    //src
    buffer[11] = 0xff;
    buffer[12] = 0xff;
    buffer[13] = 0xff;
    buffer[14] = 0xff;
    buffer[15] = 0xff;
    buffer[16] = 0xff;
    buffer[17] = 0xff;
    buffer[18] = 0xff;
    //报文序列号
    buffer[19] = 0x02;
    //负载长度
    buffer[20] = 0x00;
    buffer[21] = 0x19;

    buffer[22] = 0x20;

    buffer[23] = 0x01;
    //data

    float v=30;

    buffer[24] = 0x28;
    buffer[25] = 0x01;
    buffer[26] = 0x02;
    /*
    buffer[24] = 0x28;
    buffer[25] = 0x01;
    buffer[26] = 0x02;
    */

    //crc

    mycrcnum=myCRC16((unsigned char *)(buffer)+2,25);
    crcnum = mycrcnum/256; //crc16( tempPkt ); //crc16校验值
    crcnum2 = mycrcnum%256;

    buffer[27] = crcnum;
    buffer[28] = crcnum2;

    send(sockClient,(char *)&buffer,sizeof(buffer)+1,0);    //向服务器端发送数据
    printf("hhhhhhhhhhha\n");

    Sleep(5000);
        buffer[25] = 0x02;

    mycrcnum=myCRC16((unsigned char *)(buffer)+2,25);
    crcnum = mycrcnum/256; //crc16( tempPkt ); //crc16校验值
    crcnum2 = mycrcnum%256;


    buffer[27] = crcnum;
    buffer[28] = crcnum2;

    send(sockClient,(char *)&buffer,sizeof(buffer)+1,0);
    printf("hhhhhhhhhhha2222222\n");
    Sleep(5000);
    /*
    buffer[24] = 0x28;
    buffer[25] = 0x01;
    buffer[26] = 0x02;
    mycrcnum=myCRC16((unsigned char *)(buffer)+2,25);
    crcnum = mycrcnum/256; //crc16( tempPkt ); //crc16校验值
    crcnum2 = mycrcnum%256;
    buffer[27] = crcnum;
    buffer[28] = crcnum2;
    send(sockClient,(char *)&buffer,sizeof(buffer)+1,0);
*/
    closesocket(sockClient);                                    //关闭连接
    WSACleanup();
}

