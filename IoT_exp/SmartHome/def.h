#ifndef DEFINE_H
#define DEFINE_H
#include<QSqlQuery>
#include<QString>
#include<QDebug>
#define DEBUG

#ifdef DEBUG
#define testDB() testDB()
#else
#define testDB()
#endif

#undef uint8
#define uint8 unsigned char

#define UART_COMMAND(n) struct{ \
    uint8 head1;				\
    uint8 head2;				\
                                \
    uint8 type;                 \
    uint8 dest[8];				\
    uint8 src[8];				\
    uint8 sn;					\
    uint8 len[2];               \
    uint8 Pkt_Type;             \
    uint8 Reserved;             \
    uint8 data[n];              \
    uint8 crc[2];				\
}

#define INIT_CMD(cmd, n){       \
    cmd.head1 = 0xaa;           \
    cmd.head2 = 0x44;           \
                                \
    cmd.type = 0x02;            \
    for(int i=0;i<8;i++){       \
        cmd.dest[i] = 0xF;      \
        cmd.src[i]  = 0xF;      \
    }                           \
    cmd.sn = 0x02;              \
    cmd.len[0] = ((22+n) & 0XFF00) >> 8;       \
    cmd.len[1] = (22+n) & 0X00FF;              \
    cmd.Pkt_Type=0x20;                         \
    cmd.Reserved=0x01;                         \
}

#define UART_PACKET(n) struct { \
   uint8 head1;                 \
   uint8 head2;                 \
                                \
   uint8 type;                  \
   uint8 dest[8];               \
   uint8 src[8];                \
   uint8 sn;                    \
   uint8 len[2];                \
   uint8 Pkt_Type;              \
   uint8 Reserved;              \
   uint8 data[n];               \
   uint8 crc[2];				\
}

#define INIT_PKT(pkt, n){       \
    pkt.head1 = 0xaa;           \
    pkt.head2 = 0x44;           \
                                \
    pkt.type = 0x01;            \
    for(int i=0;i<8;i++){       \
        pkt.dest[i] = 0xF;      \
        pkt.src[i]  = 0xF;      \
    }                           \
    pkt.sn = 0x02;              \
    pkt.len[0] = ((22+n) & 0XFF00) >> 8;       \
    pkt.len[1] = (22+n) & 0X00FF;              \
    pkt.Pkt_Type=0x10;                         \
    pkt.Reserved=0x01;                         \
}

#undef  uint16
#define uint16 unsigned short

#define CAL_CRC(data, n){               \
    uint16 crcsum=0;                    \
    int len = 22 + n;                   \
    uint16* p = (uint16*)&data.type;    \
    while (len > 1){                    \
          crcsum^=*p++;                 \
          len -=2;                      \
    }                                   \
    if (len) {                          \
        crcsum^= *(uint8 *)p;           \
    }                                   \
    data.crc[0] = (crcsum & 0xFF00) >> 8; \
    data.crc[1] = (crcsum & 0x00FF)  ;  \
}

#ifdef DEBUG
#define dump(data, n) dump(data, n)
#else
#define dump(data, n)
#endif

void (testDB)();
void (dump)(void* data, int n);
void socket_test();
int mainqq();
#endif // DEFINE_H

