//
// Created by sangjun on 23. 5. 2.
//
#include "QtTCPClient.h"

extern pAXIS joystickAxis;
extern pBUTTON joystickButton;
extern pUI_COMMAND sharedCommand;
extern pSHM sharedMemory;
extern pCUSTOM_DATA sharedCustom;

pthread_t QtServer;
pthread_t QtClient;

JoystickOnex Onex;

void transJoystick()
{
    joystickAxis->LeftStickX = Onex.joy_axis[0];
    joystickAxis->LeftStickY = Onex.joy_axis[1];
    joystickAxis->LeftTrigger = Onex.joy_axis[2];
    joystickAxis->RightStickX = Onex.joy_axis[3];
    joystickAxis->RightStickY = Onex.joy_axis[4];
    joystickAxis->RightTrigger = Onex.joy_axis[5];
    joystickAxis->DpadX = Onex.joy_axis[6];
    joystickAxis->DpadY = Onex.joy_axis[7];
    joystickButton->FaceButtonA = (float)Onex.joy_button[0];
    joystickButton->FaceButtonB = (float)Onex.joy_button[1];
    joystickButton->FaceButtonX = (float)Onex.joy_button[2];
    joystickButton->FaceButtonY = (float)Onex.joy_button[3];
    joystickButton->LeftBumper = (float)Onex.joy_button[4];
    joystickButton->RightBumper = (float)Onex.joy_button[5];
    joystickButton->Back = (float)Onex.joy_button[6];
    joystickButton->Start = (float)Onex.joy_button[7];
    joystickButton->Guide = (float)Onex.joy_button[8];
    joystickButton->LeftStick = (float)Onex.joy_button[9];
    joystickButton->RightStick = (float)Onex.joy_button[10];
}

void serializeJoystickInfo(QDataStream &stream) {
    stream << joystickAxis->LeftStickX;
    stream << joystickAxis->LeftStickY;
    stream << joystickAxis->LeftTrigger;
    stream << joystickAxis->RightStickX;
    stream << joystickAxis->RightStickY;
    stream << joystickAxis->RightTrigger;
    stream << joystickAxis->DpadX;
    stream << joystickAxis->DpadY;
    stream << joystickButton->FaceButtonA;
    stream << joystickButton->FaceButtonB;
    stream << joystickButton->FaceButtonX;
    stream << joystickButton->FaceButtonY;
    stream << joystickButton->LeftBumper;
    stream << joystickButton->RightBumper;
    stream << joystickButton->Back;
    stream << joystickButton->Start;
    stream << joystickButton->Guide;
    stream << joystickButton->LeftStick;
    stream << joystickButton->RightStick;
}

void* sendData(void* arg)
{
    while (1)
    {
        Onex.Read();
        transJoystick();

        // 서버 IP 주소 및 포트 설정
        const QHostAddress serverAddress("192.168.0.124");
        const quint16 serverPort = 12345;

        // 서버에 연결
        QTcpSocket* socket = new QTcpSocket();
        socket->connectToHost(serverAddress, serverPort);

        if (socket->waitForConnected()) {
            // 보낼 데이터 생성

            QByteArray byteArray;
            QDataStream stream(&byteArray, QIODevice::WriteOnly);

            serializeJoystickInfo(stream);

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

void* receiveData(void* arg)
{
    // 서버 IP 주소 및 포트 설정
    const QHostAddress serverAddress(QHostAddress::Any);
    const quint16 serverPort = 34567;

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

void StartSendData()
{
    joystickAxis = (pAXIS)malloc(sizeof(AXIS));
    joystickButton = (pBUTTON)malloc(sizeof(BUTTON));

    pthread_create(&QtClient,NULL,sendData,NULL);
    pthread_create(&QtServer,NULL,receiveData,NULL);
    pthread_join(QtClient,NULL);
    pthread_join(QtServer,NULL);
}

