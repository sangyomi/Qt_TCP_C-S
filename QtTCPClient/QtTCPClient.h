//
// Created by sangjun on 23. 5. 2.
//

#ifndef QTTCPCLIENT_QTTCPCLIENT_H
#define QTTCPCLIENT_QTTCPCLIENT_H

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
#include "ThreadGenerator.hpp"

void StartSendData();
void* sendData(void* arg);
void* receiveData(void* arg);
void transJoystick();
void serializeJoystickInfo(QDataStream &stream);
void deserializeSharedMemoryInfo (QDataStream &stream);

#endif //QTTCPCLIENT_QTTCPCLIENT_H
