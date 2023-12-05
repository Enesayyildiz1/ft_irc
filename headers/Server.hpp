#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class Server
{
    private:
        int port;
    public:
        Server(std::string av1);
        void createSocket();
};

#endif