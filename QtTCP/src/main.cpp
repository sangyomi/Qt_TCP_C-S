//
// Created by sj on 23. 05. 10.
//

#include "../include/TcpCommunication.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    StartCommunication();

    return a.exec();
}