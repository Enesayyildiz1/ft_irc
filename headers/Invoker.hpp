#ifndef INVOKER_HPP
#define INVOKER_HPP

class Invoker;

#include"Server.hpp"
#include"libraries.hpp"
#include"Command.hpp"
#include"User.hpp"

class User;
class Command;
class Server;



class Invoker
{
    private:
        Server* _server;
        std::vector<Command*> _commands;
        
     


    public:
        Invoker(Server* server);
        void processCommand(User *sender, std::deque<std::string> args);
        void processData(User *sender, std::string data);
        std::deque<std::string> dataToArgs(std::string data);
        bool isCommand(std::string data);
		virtual ~Invoker();
};







#endif