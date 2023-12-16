#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include"libraries.hpp"
#include"Invoker.hpp"
#include"User.hpp"
#include"../channel/Channel.hpp"
class Channel;
class Server;
class User;

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
        std::vector<Channel *>	_channels;
        std::string _serverName;
        Invoker					*_Invoker;
        int createSocket();

    public:
        Server(const std::string host, const std::string port, const std::string password);
        void			greeting(int client_d)const;
        int recvMsg(User *user);
        int acceptUser();
        bool checkPassword(std::string userPassword);
        Channel			*getChannel(std::string name);
        Channel		*createChannel(std::string name, User *admin);
        std::string getPrefix() const;
        void sendMessage(User* to, std::string message);
        User *getUserById(std::string id);
        void removeUserFromPoll(std::string id) ;
        void    deleteChannel(Channel *channel);
        void removeUserFromUsers(std::string id);
        std::vector<Channel *> getChannels();
        void			removeUser(std::string id);
        User *getUser(std::string name);

        void action();
        void start();
};

#endif