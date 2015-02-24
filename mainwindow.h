#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <port.h>
#include <QThread>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <protocol_8smc4.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVector <unsigned char> receivedMesage;
    QVector <unsigned char> mesage;
    protocol_8SMC4 *p;
//    struct Settings {//Структура с настройками порта
//        QString name;
//        qint32 baudRate;
//        QSerialPort::DataBits dataBits;
//        QSerialPort::Parity parity;
//        QSerialPort::StopBits stopBits;
//        QSerialPort::FlowControl flowControl;
//    };
//    QSerialPort *serialPort;
//    Settings serialSettings;
public slots:
    void Print(QByteArray);
//    void Write_Settings_Port(QString name, int baudrate,int DataBits,int Parity,int StopBits, int FlowControl);
//    void ConnectPort(void);
//    void DisconnectPort();

//    void error_(QString err);//Сигнал ошибок порта
private slots:
//    void on_btnConnect_clicked();
//    void handleError(QSerialPort::SerialPortError error);
    void on_pushButton_3_clicked();

    void on_btnConnect_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void getDataFromPort(QByteArray);
    void getDataFromPort1(QByteArray);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_btnConnect_2_clicked();

    void on_btnDisconnect_2_clicked();

    void on_pushButton_6_clicked();

    void on_btnDisconnect_clicked();

signals:
    void  savesettings(QString name, int baudrate,int DataBits,int Parity,int StopBits, int FlowControl);
    void writeData(QByteArray);
    void writeData1(QByteArray);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
