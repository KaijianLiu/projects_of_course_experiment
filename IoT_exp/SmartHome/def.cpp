#include"def.h"
#include<iostream>
void (testDB)(){
    QSqlQuery query;
    //向每个表中插入3条记录
    bool a = true;
    a = query.exec("insert into humidity (datestamp, data) values(1461496645,12.5)");
    qDebug()<<"a1 = "<<a;
    a = query.exec("insert into humidity (datestamp, data) values(321312,25.0)");
     qDebug()<<"a2 = "<<a;
    a = query.exec("insert into humidity (datestamp, data) values(140005450987654321,100.99)");
    qDebug()<<"a3 = "<<a;

    a = query.exec("insert into temperature (datestamp, data) values(1461496645,12.5)");
    qDebug()<<"a4 = "<<a;
    a = query.exec("insert into temperature (datestamp, data) values(321312,25.0)");
     qDebug()<<"a5 = "<<a;
    a = query.exec("insert into temperature (datestamp, data) values(140005450987654321,100.99)");
    qDebug()<<"a6 = "<<a;


    a = query.exec("insert into bathroom (datestamp, operation) values(1461496645,'open')");
    qDebug()<<"a7 = "<<a;
    a = query.exec("insert into bathroom (datestamp, operation) values(321312,'close')");
     qDebug()<<"a9 = "<<a;
    a = query.exec("insert into bathroom (datestamp, operation) values(140005450987654321,'open')");
    qDebug()<<"a9 = "<<a;

    a = query.exec("insert into gate (datestamp, cardid) values(1461496645,111)");
    qDebug()<<"a10 = "<<a;
    a = query.exec("insert into gate (datestamp, cardid) values(321312,222)");
     qDebug()<<"a11 = "<<a;
    a = query.exec("insert into gate (datestamp, cardid) values(140005450987654321,333)");
    qDebug()<<"a12 = "<<a;

    // query.exec("select * from humidity");
    // query.exec("select * from temperature");
    // query.exec("select * from bathroom");
    query.exec("select * from gate");

    //query.next()指向查找到的第一条记录，然后每次后移一条记录
    while(query.next())
    {
        //query.value(0)是id的值，将其转换为int型
        int value0 = query.value(0).toInt();
        QString value1 = query.value(1).toString();
        QString value2 = query.value(2).toString();
        //输出两个值
        qDebug() << value0 << value1<<value2 ;
   }
   query.exec("delete from humidity where 1==1");
   query.exec("delete from temperature where 1==1");
   query.exec("delete from bathroom where 1==1");
   query.exec("delete from gate where 1==1");

}

void (dump)(void* dt, int n){
    uint8 * data = (uint8*)dt;
    std::cout<<"==========head=========="<<std::endl;
    std::cout<<"head1 : "<<"0x"<<std::hex<<(uint16)data[0]<<std::endl;
    std::cout<<"head2 : "<<"0x"<<std::hex<<(uint16)data[1]<<std::endl;
    std::cout<<"==========load=========="<<std::endl;
    std::cout<<"type : "<<"0x"<<std::hex<<(uint16)data[2]<<std::endl;
    std::cout<<"dest[8] : ";
    for(int i=0; i<8 ; i++)
        std::cout<<"0x"<<std::hex<<(uint16)data[3+i]<<" ";
    std::cout <<std::endl;
    std::cout<<"src[8] : ";
    for(int i=0; i<8 ; i++)
        std::cout<<"0x"<<std::hex<<(uint16)data[11+i]<<" ";
    std::cout <<std::endl;
    std::cout<<"sn : "<<"0x"<<std::hex<<(uint16)data[19]<<std::endl;
    std::cout<<"len[0] : "<<"0x"<<std::hex<<(uint16)data[20]<<std::endl;
    std::cout<<"len[1] : "<<"0x"<<std::hex<<(uint16)data[21]<<std::endl;
    std::cout<<"Pkt_Type : "<<"0x"<<std::hex<<(uint16)data[22]<<std::endl;
    std::cout<<"Reserved : "<<"0x"<<std::hex<<(uint16)data[23]<<std::endl;
    for(int i=0; i<n ; i++){
        std::cout<<"data["<<std::dec<<i<<"] : "<<"0x"<<std::hex<<(uint16)data[24+i]<<std::endl;
    }
    std::cout<<"==========crc =========="<<std::endl;
    std::cout<<"crc[0] : "<<"0x"<<std::hex<<(uint16)data[n+24]<<std::endl;
    std::cout<<"crc[1] : "<<"0x"<<std::hex<<(uint16)data[n+25]<<std::endl;

}
