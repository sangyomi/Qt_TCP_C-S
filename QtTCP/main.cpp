#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <pthread.h>
#include "RobotDescription.hpp"
#include "SharedMemory.hpp"

pthread_t QtServer;
pthread_t QtClient;

void* receiveData(void *arg)
{
    // 서버 IP 주소 및 포트 설정
    const QHostAddress serverAddress(QHostAddress::Any);
    const quint16 serverPort = 12345;

    // 서버 생성 및 연결 대기
    QTcpServer server;
    server.listen(serverAddress, serverPort);

    // 클라이언트 연결 대기 및 처리
    while (server.isListening()) {
        if (server.waitForNewConnection()) {
            QTcpSocket *socket = server.nextPendingConnection();

            if (socket) {
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

                // 응답 전송
                QByteArray requestData;
                QDataStream out(&requestData, QIODevice::WriteOnly);
                out << (qint64)0;
                out.device()->seek(0);
                out << (qint64)data.size();

                socket->write(requestData);
                socket->write(data);
                socket->flush();

                // 소켓 및 데이터 삭제
                socket->disconnectFromHost();
                socket->deleteLater();
            }
        }
    }
}

void* sendData(void* arg)
{
    while(1)
    {
        // 서버 IP 주소 및 포트 설정
        const QHostAddress serverAddress("192.168.0.124");
        const quint16 serverPort = 34567;

        // 서버에 연결
        QTcpSocket* socket = new QTcpSocket();
        socket->connectToHost(serverAddress, serverPort);

        if (socket->waitForConnected()) {
            // 보낼 데이터 생성

            QByteArray byteArray;
            QDataStream stream(&byteArray, QIODevice::WriteOnly);

//        serializeJoystickInfo(stream);

            // 데이터 전송
            QByteArray requestData;
            QDataStream out(&requestData, QIODevice::WriteOnly);
            out << (qint64)0;
            out.device()->seek(0);
            out << (qint64)byteArray.size();

            socket->write(requestData);
            socket->write(byteArray);
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

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    pthread_create(&QtClient,NULL,sendData,NULL);
    pthread_create(&QtServer,NULL,receiveData,NULL);
    pthread_join(QtClient,NULL);
    pthread_join(QtServer,NULL);

    return a.exec();
}