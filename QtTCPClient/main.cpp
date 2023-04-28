#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <iostream>
#include "JoystickOnex.h"

JoystickOnex Onex;

void sendData()
{
    // 서버 IP 주소 및 포트 설정
    const QHostAddress serverAddress("192.168.0.124");
    const quint16 serverPort = 12345;

    // 서버에 연결
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(serverAddress, serverPort);

    if (socket->waitForConnected()) {
        // 보낼 데이터 생성

        float axis[100];
        std::copy(Onex.joy_axis.begin(), Onex.joy_axis.end(), axis);

        float button[100];
        std::copy(Onex.joy_button.begin(), Onex.joy_button.end(), button);

        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);
        dataStream << button[0] << axis[1] << axis[2] << axis[3] << axis[4] << axis[5] << axis[6] << axis[7];

        // 데이터 전송
        QByteArray requestData;
        QDataStream out(&requestData, QIODevice::WriteOnly);
        out << (qint64)0;
        out.device()->seek(0);
        out << (qint64)data.size();

        socket->write(requestData);
        socket->write(data);
        socket->flush();

        // 응답 수신
        if (socket->waitForReadyRead()) {
            // 데이터 수신
            QDataStream in(socket);
            in.setVersion(QDataStream::Qt_5_0);

            qint64 blockSize = 0;
            if (socket->bytesAvailable() < sizeof(qint64)) {
                socket->waitForReadyRead();
            }
            in >> blockSize;

            QByteArray data;
            while (socket->bytesAvailable() < blockSize) {
                socket->waitForReadyRead();
            }
            data = socket->read(blockSize);

            // 데이터 처리
            QDataStream dataStream(&data, QIODevice::ReadOnly);
            float number[100];
            dataStream >> number[0] >> number[1] >> number[2] >> number[3] >> number[4] >> number[5]>> number[6] >> number[7];

            if (dataStream.status() != QDataStream::Ok) {
                qWarning() << "Error while reading data: " << dataStream.status();
            } else {
                qDebug() << "Received numbers: " << number[0] << ", " << number[1] << ", " << number[2] << ", " << number[3] << ", " << number[4] << ", " << number[5] << ", " << number[6] << ", " << number[7];
            }
            socket->disconnectFromHost();
            socket->deleteLater();
        }
    } else {
        qWarning() << "Could not connect to server: " << socket->errorString();
    }
}


int main(int argc, char *argv[])
{
//
//    while (true)
//    {

//    }
    while (true)
    {
        Onex.Read();
        QCoreApplication a(argc, argv);
        sendData();
    }
    return 0;
}
