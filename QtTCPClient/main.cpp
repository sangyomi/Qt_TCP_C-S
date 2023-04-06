#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "joy.h"

using namespace std;

int main()
{
    JoyStick joystick;

    joystick.read();

    return 0;
}


//#include <QTcpSocket>
//#include <QDataStream>
//#include <QCoreApplication>
//#include <QHostAddress>
//
//void sendData()
//{
//    // 서버 IP 주소 및 포트 설정
//    const QHostAddress serverAddress("127.0.0.1");
//    const quint16 serverPort = 12345;
//
//    // 서버에 연결
//    QTcpSocket* socket = new QTcpSocket();
//    socket->connectToHost(serverAddress, serverPort);
//
//    if (socket->waitForConnected()) {
//        // 보낼 데이터 생성
//        float number = 4212.2;
//        QByteArray data;
//        QDataStream dataStream(&data, QIODevice::WriteOnly);
//        dataStream << number;
//
//        // 데이터 전송
//        QByteArray requestData;
//        QDataStream out(&requestData, QIODevice::WriteOnly);
//        out << (qint64)0;
//        out.device()->seek(0);
//        out << (qint64)data.size();
//
//        socket->write(requestData);
//        socket->write(data);
//        socket->flush();
//
//        // 응답 수신
//        if (socket->waitForReadyRead()) {
//            // 데이터 수신
//            QDataStream in(socket);
//            in.setVersion(QDataStream::Qt_5_0);
//
//            qint64 blockSize = 0;
//            if (socket->bytesAvailable() < sizeof(qint64)) {
//                socket->waitForReadyRead();
//            }
//            in >> blockSize;
//
//            QByteArray data;
//            while (socket->bytesAvailable() < blockSize) {
//                socket->waitForReadyRead();
//            }
//            data = socket->read(blockSize);
//
//            // 데이터 처리
//            QDataStream dataStream(&data, QIODevice::ReadOnly);
//            float number = 0;
//            dataStream >> number;
//
//            if (dataStream.status() != QDataStream::Ok) {
//                qWarning() << "Error while reading data: " << dataStream.status();
//            } else {
//                qDebug() << "Received number: " << number;
//            }
//            socket->disconnectFromHost();
//            socket->deleteLater();
//        }
//    } else {
//        qWarning() << "Could not connect to server: " << socket->errorString();
//    }
//}
//
//
//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    sendData();
//    return a.exec();
//}
