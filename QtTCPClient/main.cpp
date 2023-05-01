#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <iostream>
#include "JoystickOnex.h"

JoystickOnex Onex;

void sendData()
{
    Onex.Read();

    // 서버 IP 주소 및 포트 설정
    const QHostAddress serverAddress("192.168.0.124");
    const quint16 serverPort = 12345;

    // 서버에 연결
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(serverAddress, serverPort);

    if (socket->waitForConnected()) {
        // 보낼 데이터 생성

        QVector<float> axisVector;
        QVector<float> buttonVector;

        for (int value: Onex.joy_axis)
        {
            axisVector.append(static_cast<float>(value));
        }

        for (char value: Onex.joy_button)
        {
            buttonVector.append(static_cast<float>(value));
        }

        QByteArray data;
        QDataStream dataStream(&data, QIODevice::WriteOnly);

        foreach (float value, axisVector)
        {
            dataStream << value;
        }

        foreach (float value, buttonVector)
        {
            dataStream << value;
        }

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

            QVector<float> axisVector;
            QVector<float> buttonVector;
            int count = 0;

            while (!dataStream.atEnd())
            {
                float value;
                dataStream >> value;
                if (count < 8)
                {
                    axisVector.append(value);
                }
                else
                {
                    buttonVector.append(value);
                }
                count++;
            }

            if (dataStream.status() != QDataStream::Ok) {
                qWarning() << "Error while reading data: " << dataStream.status();
            }
            else
            {
                qDebug() << "axisVector" << axisVector;
                qDebug() << "buttonVector" << buttonVector;
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
    while (true)
    {
        QCoreApplication a(argc, argv);
        sendData();
    }
    return 0;
}
