#ifndef COMMAND_HPP
#define COMMAND_HPP

#include"libraries.hpp"
#include "Command.hpp"
#include "User.hpp"
#include "Server.hpp"
#include "ircserv.hpp"
#include "../channel/Channel.hpp"

class Server;
class User;

class Command
{
    protected:
        std::string _name;
        std::string _description;
        Server*     _server;
        User*       _sender;
        std::deque<std::string> _args;
    public:
        Command();
        virtual ~Command();
        
        std::string getName() const;
        std::string getDescription() const;

        void setSender(User *sender);
        void setServer(Server* server);
        void setArgs(std::deque<std::string> args);

        virtual void execute() = 0;
};


#endif