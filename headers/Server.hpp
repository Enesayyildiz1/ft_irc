#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include"libraries.hpp"
#include"Invoker.hpp"
#include"User.hpp"


class Server;

# define MAX_CONNECTION				1000

class Server
{
    private:
        int						_sock;
		const std::string		_host;
		const std::string		_port;
		const std::string		_password;
        std::vector<pollfd>		_pollfds;
        std::vector<User *>     _users;
        std::string _serverName;
        Invoker					*_Invoker;
        int createSocket();
    public:
        Server(const std::string host, const std::string port, const std::string password);
        void			greeting(int client_d)const;
        int recvMsg(User *user);
        int acceptUser();
        void action();
        void start();
};

#endif