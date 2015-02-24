#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    serialPort = new QSerialPort;
//    connect(serialPort, SIGNAL(error_(QString)), this, SLOT());//Лог ошибок
//    connect(ui->btnConnect,SIGNAL(clicked()),this,SLOT(ConnectPort()));
//    connect(this, SIGNAL)
    QThread *thread_New = new QThread;//Создаем поток для порта платы
    Port *PortNew = new Port();//Создаем обьект по классу
    PortNew->moveToThread(thread_New);//помешаем класс  в поток
    PortNew->thisPort.moveToThread(thread_New);//Помещаем сам порт в поток

    QThread *thread_New1 = new QThread;//Создаем поток для порта платы
    Port *PortNew1 = new Port();//Создаем обьект по классу
    PortNew1->moveToThread(thread_New1);//помешаем класс  в поток
    PortNew1->thisPort.moveToThread(thread_New1);//Помещаем сам порт в поток

    connect(PortNew, SIGNAL(error_(QByteArray)), this, SLOT(Print(QByteArray)));//Лог ошибок
    connect(thread_New, SIGNAL(started()), PortNew, SLOT(process_Port()));//Переназначения метода run
    connect(PortNew, SIGNAL(finished_Port()), thread_New, SLOT(quit()));//Переназначение метода выход
    connect(thread_New, SIGNAL(finished()), PortNew, SLOT(deleteLater()));//Удалить к чертям поток
    connect(PortNew, SIGNAL(finished_Port()), thread_New, SLOT(deleteLater()));//Удалить к чертям поток
    connect(this,SIGNAL(savesettings(QString,int,int,int,int,int)),PortNew,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(ui->btnConnect, SIGNAL(clicked()),PortNew,SLOT(ConnectPort()));//по нажатию кнопки подключить порт
    connect(ui->btnDisconnect, SIGNAL(clicked()),PortNew,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
//    connect(PortNew, SIGNAL(outPort(QString)), this, SLOT(Print(QString)));//вывод в текстовое поле считанных данных
    connect(this,SIGNAL(writeData(QByteArray)),PortNew,SLOT(WriteToPort(QByteArray)));//отправка в порт данных
    connect(PortNew,SIGNAL(outPort(QByteArray)),this,SLOT(getDataFromPort(QByteArray)));

    connect(PortNew1, SIGNAL(error_(QByteArray)), this, SLOT(Print(QByteArray)));//Лог ошибок
    connect(thread_New1, SIGNAL(started()), PortNew1, SLOT(process_Port()));//Переназначения метода run
    connect(PortNew1, SIGNAL(finished_Port()), thread_New1, SLOT(quit()));//Переназначение метода выход
    connect(thread_New1, SIGNAL(finished()), PortNew1, SLOT(deleteLater()));//Удалить к чертям поток
    connect(PortNew1, SIGNAL(finished_Port()), thread_New1, SLOT(deleteLater()));//Удалить к чертям поток
    connect(this,SIGNAL(savesettings(QString,int,int,int,int,int)),PortNew1,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));//Слот - ввод настроек!
    connect(ui->btnConnect_2, SIGNAL(clicked()),PortNew1,SLOT(ConnectPort()));//по нажатию кнопки подключить порт
    connect(ui->btnDisconnect_2, SIGNAL(clicked()),PortNew1,SLOT(DisconnectPort()));//по нажатию кнопки отключить порт
//    connect(PortNew, SIGNAL(outPort(QString)), this, SLOT(Print(QString)));//вывод в текстовое поле считанных данных
    connect(this,SIGNAL(writeData1(QByteArray)),PortNew1,SLOT(WriteToPort(QByteArray)));//отправка в порт данных
    connect(PortNew1,SIGNAL(outPort(QByteArray)),this,SLOT(getDataFromPort1(QByteArray)));

    thread_New->start();
    thread_New1->start();
    p = new protocol_8SMC4;
    qDebug() << sizeof(protocol_8SMC4::POS);
//    p.createSSTSmessage();
//     qDebug()<<"sizeof struct"<<sizeof(protocol_8SMC4::SSTS);

}

void MainWindow::getDataFromPort(QByteArray data)
{
    receivedMesage.clear();
    qDebug()<<data.toHex();
    for(int i = 0; i < data.size(); i++)
        receivedMesage.append(data.at(i));
    p->setReceivedMessage(receivedMesage);
    ui->plainTextEdit_3->appendPlainText(data);
}

void MainWindow::getDataFromPort1(QByteArray data)
{
    receivedMesage.clear();
//    qDebug()<<data.toHex();
    for(int i = 0; i < data.size(); i++)
        receivedMesage.append(data.at(i));
    ui->plainTextEdit_2->appendPlainText(data);
//    ui->plainTextEdit_3->appendPlainText(data);
//    p->setReceivedMessage(receivedMesage);
}
//void MainWindow::savesettings(QString name, int baudrate,int DataBits,int Parity,int StopBits, int FlowControl)
//{
//    name = ui->lineEdit->text();
//    baudrate = 115200;
//    DataBits = 8;
//    Parity = 0;
//    StopBits = 2;
//    FlowControl = 0;
//}

void MainWindow::Print(QByteArray printdata)
{
   // QByteArray t= printdata.toLocal8Bit();
    qDebug() << printdata.toHex();
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_3_clicked()
{
    p->createMOVRmessage(ui->doubleSpinBox->value()/0.015);
    QByteArray tmparr;
    for(int i = 0; i < p->message.size();i++)
        tmparr.append(p->message[i]);
    emit writeData(tmparr);
}

void MainWindow::on_btnConnect_clicked()
{
    emit savesettings(ui->lineEdit->text(),115200,8,0,2,0);
}


void MainWindow::on_pushButton_2_clicked()
{
    emit writeData(ui->plainTextEdit->toPlainText().toLocal8Bit());
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{
   // p->createSSTSmessage();
    p->createSENGmessage(9);
    qDebug() << "message size" << p->message.size();
    QByteArray tmparr;
    for(int i = 0; i < p->message.size();i++)
        tmparr.append(p->message[i]);
    emit writeData(tmparr);
}

void MainWindow::on_pushButton_5_clicked()
{
    p->createMOVEmessage(ui->doubleSpinBox->value()/0.015);
    QByteArray tmparr;
    for(int i = 0; i < p->message.size();i++)
        tmparr.append(p->message[i]);
    emit writeData(tmparr);
}

void MainWindow::on_btnConnect_2_clicked()
{
    emit savesettings(ui->lineEdit_2->text(),115200,8,0,2,0);
}

void MainWindow::on_btnDisconnect_2_clicked()
{

}

void MainWindow::on_pushButton_6_clicked()
{
    emit writeData1(ui->plainTextEdit_4->toPlainText().toLocal8Bit());
}

void MainWindow::on_btnDisconnect_clicked()
{

}
