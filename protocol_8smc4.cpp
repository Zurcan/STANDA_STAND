#include "protocol_8smc4.h"

protocol_8SMC4::protocol_8SMC4()
{

}

unsigned short protocol_8SMC4::calcCRC(QVector <unsigned char> pbuf, unsigned short n)
{

    unsigned short crc, i, j, carry_flag, a;
    crc = 0xffff;
    for(i = 4; i < n; i++)
    {
        crc = crc ^ pbuf[i];
        for(j = 0; j < 8; j++)
        {
            a = crc;
            carry_flag = a & 0x0001;
            crc = crc >> 1;
            if ( carry_flag == 1 ) crc = crc ^ 0xa001;
        }
    }
//    crc = (crc<<8)|(crc>>8);
    return crc;

}

void protocol_8SMC4::setReceivedMessage(QVector<unsigned char> recmes)
{
    recmessage.clear();
    recmessage = recmes;
    if((recmessage.at(0)==0x67)&(recmessage.at(1)==0x65)&(recmessage.at(2)==0x6e)&(recmessage.at(3)==0x67))//geng
    {
        tmpSeng = new SENG;
        char *tmpArr = (char*)malloc(sizeof(SENG));

        qDebug() << sizeof(SENG);
        for(int i = 0; i < sizeof(SENG);i++)
            tmpArr[i] = recmessage.at(i);
        qDebug() << "!";
        tmpSeng =  (SENG*)tmpArr;
        qDebug() <<"tmpSeng->MicrostepMode" <<tmpSeng->MicrostepMode;
        qDebug() << "tmpSeng->StepsPerRev" << tmpSeng->StepsPerRev;
        qDebug() <<"tmpSeng->AntiPlay" <<tmpSeng->AntiPlay;
        qDebug() <<"tmpSeng->NomCurrent" <<tmpSeng->NomCurrent;
        qDebug() <<"tmpSeng->NomVoltage" <<tmpSeng->NomVoltage;
        qDebug() <<"tmpSeng->NomSpeed" <<tmpSeng->NomSpeed;
        qDebug() <<"tmpSeng->uNomSpeed" <<tmpSeng->uNomSpeed;
        qDebug() <<"tmpSeng->EngineFlags" <<tmpSeng->EngineFlags;
        recmessage.remove(recmessage.size()-1);
        recmessage.remove(recmessage.size()-1);
        qDebug() << calcCRC(recmessage,recmessage.size());

//        createSENGmessage(1);
    }
    if((recmessage.at(0)==0x67)&(recmessage.at(1)==0x70)&(recmessage.at(2)==0x6f)&(recmessage.at(3)==0x73))//gpos
    {
        POS *tmpPos;
        char *tmpArr = (char*)malloc(sizeof(POS));
        for(int i = 0; i < sizeof(POS);i++)
            tmpArr[i] = recmessage.at(i);
        tmpPos = (POS*)tmpArr;
        qDebug() << "Position" << tmpPos->Position;
        qDebug() << "uPosition"<< tmpPos->uPosition;
        qDebug() << "EncPosition" << tmpPos->EncPosition;

    }
//    delete tmpArr;
}
void protocol_8SMC4::createMOVRmessage(double delta)
{
    message.clear();
    MOVR *movrMes = new MOVR;
    int sign;
    if(delta<0)
        sign=-1;
    else
        sign =1;
    short tmpUdelta = (delta*sign - ((int)delta*sign))*255;
    qDebug() <<"tmpUdelta" <<tmpUdelta;
    qDebug() << "signed delta"<< (signed int)delta;
    movrMes->CMD = 0x72766F6D;
//    delta = -100;
    movrMes->DeltaPosition = (signed int)delta;
    movrMes->uDeltaPosition = tmpUdelta*sign;
    char *tmpArr;
    tmpArr = (char*)movrMes;
    for(int i = 0; i < sizeof(MOVR);i++)
        message.append(tmpArr[i]);
    short tmpCRC = calcCRC(message,message.size());
    message.append(tmpCRC);
    message.append(tmpCRC>>8);
    QByteArray tmpArr1;
    for(int i = 0; i < message.size();i++)
        tmpArr1.append(message.at(i));
        qDebug() << tmpArr1.toHex();
}

void protocol_8SMC4::createMOVEmessage(double delta)
{
    message.clear();
    MOVR *movrMes = new MOVR;
    int sign;
    if(delta<0)
        sign=-1;
    else
        sign =1;
    short tmpUdelta = (delta*sign - ((int)delta*sign))*255;
    qDebug() << "delta" << delta;
    qDebug() <<"tmpUdelta" <<tmpUdelta;
    qDebug() << "signed delta"<< (signed int)delta;
    movrMes->CMD = 0x65766F6D;
    movrMes->DeltaPosition = (signed int)delta;
    movrMes->uDeltaPosition = tmpUdelta*sign;
    char *tmpArr;
    tmpArr = (char*)movrMes;
    for(int i = 0; i < sizeof(MOVR);i++)
        message.append(tmpArr[i]);
    short tmpCRC = calcCRC(message,message.size());
    message.append(tmpCRC);
    message.append(tmpCRC>>8);
}

void protocol_8SMC4::createSSTSmessage()
{
    message.clear();
//    message.append();
    SSTS *sstsMes = new SSTS;
    sstsMes->CMD = 0x73747373;
    sstsMes->LeadScrewPitch = 100;
    sstsMes->Units[0] = 68;
    sstsMes->Units[1] = 69;
    sstsMes->Units[2] = 71;
    char *tmpArr;
    tmpArr = (char*)sstsMes;
    for(int i = 0; i < sizeof(SSTS);i++)
        message.append(tmpArr[i]);
    short tmpCRC;
    tmpCRC = calcCRC(message,message.size());
    message.append(tmpCRC);
    message.append(tmpCRC>>8);
    for(int i = 0; i < message.size(); i++)
        qDebug() << message.at(i);

}

void protocol_8SMC4::createSENGmessage(unsigned char microstep)
{
//    message.clear();
//    message.append();
//    SSTS *sengMes = new SENG;
    message.clear();
    tmpSeng->CMD = 0x676E6573;
    tmpSeng->MicrostepMode = 1;
    tmpSeng->NomVoltage = 0;
    tmpSeng->NomCurrent = 0;
    tmpSeng->NomSpeed = 0;
    tmpSeng->uNomSpeed = 0;
    tmpSeng->EngineFlags = 0;
    tmpSeng->AntiPlay = 0;
    tmpSeng->StepsPerRev = 1000;
    for(int i =0; i < 12;i++)
        tmpSeng->Reserved[i]=0;
    char *tmpArr = (char*)malloc(sizeof(SENG));
    tmpArr = (char*)tmpSeng;
    for(int i = 0; i < sizeof(SENG);i++)
        message.append(tmpArr[i]);
    short tmpCRC;
    tmpCRC = calcCRC(message,message.size());
    message.append(tmpCRC);
    message.append(tmpCRC>>8);
    QByteArray tmpByteArr;
    for(int i = 0; i < message.size(); i++)
    {
      tmpByteArr.append(message.at(i));
    }
    qDebug() << tmpByteArr.toHex();

}
protocol_8SMC4::~protocol_8SMC4()
{

}

