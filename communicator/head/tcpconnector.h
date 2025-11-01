#ifndef TCPCONNECTOR_H
#define TCPCONNECTOR_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <QString>
#include <exception>
#include "../head/generalvariables.h"


typedef struct sockaddr_in Socket;

/**
   Klasa tworząca połączenie TCP
 * @brief The TCPConnector class
 */
class TCPConnector
{
public:
    TCPConnector();
    ~TCPConnector();
    std::string Read(std::__cxx11::string _my_id);
    int Write(const std::string _input);
private:
    Socket server_conn; // Gniazdo do komunikacji z serwerem
    int socket_cli;

};


/**
    Klasa do rzucania wyjątku przy tworzeniu połączenia TCP
 * @brief The TCPException class
 */
class TCPException : std::exception
{
public:
    QString opis;
    TCPException (QString _opis) : opis(_opis) {}
};


#endif // TCPCONNECTOR_H
