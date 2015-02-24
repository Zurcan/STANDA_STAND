#ifndef PROTOCOL_8SMC4_H
#define PROTOCOL_8SMC4_H
#include <QVector>
#include <QDebug>
//#pragma pack(1)
class protocol_8SMC4
{
public:
    protocol_8SMC4();
    ~protocol_8SMC4();
    void createSSTSmessage();
    void createMOVRmessage(double delta);
    void createMOVEmessage(double delta);
    void createSENGmessage(unsigned char microstep);
    void setReceivedMessage(QVector <unsigned char> recmes);
    void createSPOSmessage(int position, short uposition, long long encposition);
#pragma pack(push,1)
    struct POS
    {
        int CMD;
        signed int Position;
        signed short uPosition;
        long long EncPosition;
        unsigned char PosFlags;
        unsigned char Reserved[5];
    };
#pragma pack(pop)
#pragma pack(push, 1)
    struct SSTS
    {
        int CMD;
        float LeadScrewPitch;
        char Units[8];
        float MaxSpeed;
        float TravelRange;
        float SupplyVoltage1;
        float SupplyVoltage2;
        float MaxCurrentConsumption;
        float HorizontalLoadCapacity;
        float VerticalLoadCapacity;
        unsigned char Reserved[24];
//        unsigned short CRC;
    }sstsmes;
#pragma pack(pop)
#pragma pack(push, 1)
    struct MOVR
    {
        int CMD;
        unsigned int DeltaPosition;
        signed short uDeltaPosition;
        char Reserved[6];
//        unsigned short CRC;
    };
#pragma pack(pop)
#pragma pack(push,1)
    struct SENG
    {
        int CMD;
        unsigned short NomVoltage;
        unsigned short NomCurrent;
        unsigned int NomSpeed;
        unsigned char uNomSpeed;
        unsigned short EngineFlags;
        short AntiPlay;
        unsigned char MicrostepMode;
        unsigned short StepsPerRev;
        char Reserved[12];
    };
#pragma pack(pop)
    SENG *tmpSeng;
    QVector <unsigned char> message;
    QVector <unsigned char> recmessage;
private:
//    MOVR movrMes;

    unsigned short calcCRC(QVector<unsigned char> pbuf, unsigned short n);


};

#endif // PROTOCOL_8SMC4_H
