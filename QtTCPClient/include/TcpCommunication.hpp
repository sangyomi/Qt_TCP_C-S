//
// Created by sangjun on 23. 5. 2.
//

#ifndef QTTCPCLIENT_TCPCOMMUNICATION_HPP
#define QTTCPCLIENT_TCPCOMMUNICATION_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <QHostAddress>
#include <QtCore>
#include <pthread.h>
#include "JoystickOnex.h"
#include "SharedMemory.hpp"
#include "RobotDescription.hpp"
#include "JoystickInfo.hpp"

void StartSendData();
void* sendData(void* arg);
void* receiveData(void* arg);
void transJoystick();
void serializeJoystickInfo(QDataStream &stream);
void deserializeJoystickInfo(QDataStream &stream);
void deserializeSharedMemoryInfo (QDataStream &stream);

#endif //QTTCPCLIENT_TCPCOMMUNICATION_HPP
