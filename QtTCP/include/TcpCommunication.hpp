//
// Created by sangjun on 23. 5. 10.
//

#ifndef QTTCP_TCPCOMMUNICATION_HPP
#define QTTCP_TCPCOMMUNICATION_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QCoreApplication>
#include <QtCore>
#include <pthread.h>
#include "RobotDescription.hpp"
#include "SharedMemory.hpp"
#include "JoystickInfo.hpp"

void deserializeJoystickInfo(QDataStream &stream);
void serializeSharedMemoryInfo (QDataStream &stream);
void* receiveData(void *arg);
void* sendData(void* arg);
void StartCommunication();


#endif //QTTCP_TCPCOMMUNICATION_HPP
