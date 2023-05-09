//
// Created by sangjun on 23. 5. 2.
//
#include "../include/TcpCommunication.hpp"

pAXIS joystickAxis;
pBUTTON joystickButton;
pUI_COMMAND sharedCommand;
pSHM sharedMemory;
pCUSTOM_DATA sharedCustom;

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

void deserializeJoystickInfo(QDataStream &stream) {
    stream >> joystickAxis->LeftStickX;
    stream >> joystickAxis->LeftStickY;
    stream >> joystickAxis->LeftTrigger;
    stream >> joystickAxis->RightStickX;
    stream >> joystickAxis->RightStickY;
    stream >> joystickAxis->RightTrigger;
    stream >> joystickAxis->DpadX;
    stream >> joystickAxis->DpadY;
    stream >> joystickButton->FaceButtonA;
    stream >> joystickButton->FaceButtonB;
    stream >> joystickButton->FaceButtonX;
    stream >> joystickButton->FaceButtonY;
    stream >> joystickButton->LeftBumper;
    stream >> joystickButton->RightBumper;
    stream >> joystickButton->Back;
    stream >> joystickButton->Start;
    stream >> joystickButton->Guide;
    stream >> joystickButton->LeftStick;
    stream >> joystickButton->RightStick;
}

void deserializeSharedMemoryInfo (QDataStream &stream)
{
    stream >> sharedCommand->userCommand;
    QString string;
    stream >> string;
    QByteArray byteArray = string.toUtf8();
    Q_ASSERT(byteArray.size() <= MAX_COMMAND_DATA);
    qstrncpy(sharedCommand->userParamChar, byteArray.constData(), MAX_COMMAND_DATA);
    stream.readRawData(reinterpret_cast<char*>(sharedCommand->userParamInt), MAX_COMMAND_DATA * sizeof(int));
    stream.readRawData(reinterpret_cast<char*>(sharedCommand->userParamDouble), MAX_COMMAND_DATA * sizeof(double ));
//    stream.readRawData(reinterpret_cast<char*>(sharedMemory->gaitTable), 10 * sizeof(int));
    stream >> sharedMemory->newCommand;
    stream >> sharedMemory->can1Status;
    stream >> sharedMemory->can2Status;
    stream >> sharedMemory->motorStatus;
    stream >> sharedMemory->motorBackState;
    stream >> sharedMemory->motorForeState;
    stream >> sharedMemory->LowControlState;
    stream >> sharedMemory->HighControlState;
    stream >> sharedMemory->visualState;
    stream >> sharedMemory->gaitState;
    stream >> sharedMemory->can1State;
    stream >> sharedMemory->can2State;
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorErrorStatus), MOTOR_NUM * sizeof(int));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorTemp), MOTOR_NUM * sizeof(int));
    stream >> sharedMemory->localTime;
    stream >> sharedMemory->basePosition(0) >> sharedMemory->basePosition(1) >> sharedMemory->basePosition(2);
    stream >> sharedMemory->baseVelocity(0) >> sharedMemory->baseVelocity(1) >> sharedMemory->baseVelocity(2);
    stream >> sharedMemory->baseDesiredPosition(0) >> sharedMemory->baseDesiredPosition(1) >> sharedMemory->baseDesiredPosition(2);
    stream >> sharedMemory->baseDesiredVelocity(0) >> sharedMemory->baseDesiredVelocity(1) >> sharedMemory->baseDesiredVelocity(2);
    for (int i = 0 ; i < 4 ; ++i){
        stream >> sharedMemory->mpcTorque[i](0) >> sharedMemory->mpcTorque[i](1) >> sharedMemory->mpcTorque[i](2);
    }
    for (int i = 0 ; i < 4 ; ++i){
        stream >> sharedMemory->bodyFootPosition[i](0) >> sharedMemory->bodyFootPosition[i](1) >> sharedMemory->bodyFootPosition[i](2);
    }
    for (int i = 0 ; i < 4 ; ++i){
        stream >> sharedMemory->globalFootPosition[i](0) >> sharedMemory->globalFootPosition[i](1) >> sharedMemory->globalFootPosition[i](2);
    }
    stream >> sharedMemory->baseQuartPosition(0) >> sharedMemory->baseQuartPosition(1) >> sharedMemory->baseQuartPosition(2);
    stream >> sharedMemory->desiredLinearVelocity(0) >> sharedMemory->desiredLinearVelocity(1) >> sharedMemory->desiredLinearVelocity(2);
    stream >> sharedMemory->desiredAngularVelocity(0) >> sharedMemory->desiredAngularVelocity(1) >> sharedMemory->desiredAngularVelocity(2);
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->baseAcceleration), 3 * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->baseEulerPosition), 3 * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->baseEulerVelocity), 3 * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorPosition), MOTOR_NUM * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorVelocity), MOTOR_NUM * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorTorque), MOTOR_NUM * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorDesiredTorque), MOTOR_NUM * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedMemory->motorVoltage), MOTOR_NUM * sizeof(double));
    stream >> sharedMemory->gaitIteration;
    stream.readRawData(reinterpret_cast<char*>(sharedCustom->customVariableDouble), MAX_COMMAND_DATA * sizeof(double));
    stream.readRawData(reinterpret_cast<char*>(sharedCustom->customVariableInt), MAX_COMMAND_DATA * sizeof(int));
}

void* sendData(void* arg)
{
    while (1)
    {
        Onex.Read();
        transJoystick();

        const QHostAddress serverAddress("192.168.0.113");
        const quint16 serverPort = 12345;

        QTcpSocket* socket = new QTcpSocket();
        socket->connectToHost(serverAddress, serverPort);

        if (socket->waitForConnected()) {

            QByteArray byteArray;
            QDataStream stream(&byteArray, QIODevice::WriteOnly);

            serializeJoystickInfo(stream);

            QByteArray requestData;
            QDataStream out(&requestData, QIODevice::WriteOnly);
            out << (qint64)0;
            out.device()->seek(0);
            out << (qint64)byteArray.size();

            socket->write(requestData);
            socket->write(byteArray);
            socket->flush();

            if (socket->waitForReadyRead()) {
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

                QDataStream dataStream(&data, QIODevice::ReadOnly);

                deserializeJoystickInfo(dataStream);

                if (dataStream.status() != QDataStream::Ok) {
                    qWarning() << "Error while reading data: " << dataStream.status();
                }
                else
                {
//                    qDebug() << "serializeJoystickInfo is done";
                    qDebug() << "joystickButton->FaceButtonA:" << joystickButton->FaceButtonA;
//                    qDebug() << "joystickAxis->LeftTrigger:" << joystickAxis->LeftTrigger;
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
    const QHostAddress serverAddress(QHostAddress::Any);
    const quint16 serverPort = 34567;

    QTcpServer server;
    server.listen(serverAddress, serverPort);

    while (server.isListening()) {
        if (server.waitForNewConnection()) {
            QTcpSocket *socket = server.nextPendingConnection();

            if (socket) {
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

                QDataStream dataStream(&data, QIODevice::ReadOnly);

                deserializeSharedMemoryInfo(dataStream);

                if (dataStream.status() != QDataStream::Ok) {
                    qWarning() << "Error while reading data: " << dataStream.status();
                }
                else
                {
//                    qDebug() << "deserializeSharedMemoryInfo is done";
                    qDebug() << "sharedCommand->userCommand: " << sharedCommand->userCommand;
//                    qDebug() << "sharedCommand->userParamChar: " << sharedCommand->userParamChar;
//                    qDebug() << "sharedCommand->userParamInt: " << sharedCommand->userParamInt[0];
//                    qDebug() << "sharedCommand->userParamDouble: " << sharedCommand->userParamDouble[0];
                }

                QByteArray requestData;
                QDataStream out(&requestData, QIODevice::WriteOnly);
                out << (qint64)0;
                out.device()->seek(0);
                out << (qint64)data.size();

                socket->write(requestData);
                socket->write(data);
                socket->flush();

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
    sharedCommand = (pUI_COMMAND)malloc(sizeof(UI_COMMAND));
    sharedMemory = (pSHM)malloc(sizeof(SHM));
    sharedCustom = (pCUSTOM_DATA)malloc(sizeof(CUSTOM_DATA));

    pthread_create(&QtClient,NULL,sendData,NULL);
    pthread_create(&QtServer,NULL,receiveData,NULL);
    pthread_join(QtClient,NULL);
    pthread_join(QtServer,NULL);
}
