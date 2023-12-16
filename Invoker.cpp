#include "headers/Invoker.hpp"
#include "headers/ircserv.hpp"
#include "headers/HelpCommand.hpp"
#include "headers/PassCommand.hpp"
#include "headers/NickCommand.hpp"
#include "headers/UserCommand.hpp"
#include "headers/NoticeCommand.hpp"
#include "headers/JoinCommand.hpp"
#include "headers/PrivateMessageCommand.hpp"
#include "headers/KickCommand.hpp"
#include "headers/ListCommand.hpp"
#include "headers/PartCommand.hpp"
#include "headers/QuitCommand.hpp"
Invoker::Invoker(Server *server) : _server(server)
{

    //std::cout <<server<<"Selam" <<std::endl; 
    _commands.push_back(new HelpCommand(_commands));
    _commands.push_back(new PassCommand());
    _commands.push_back(new NickCommand());
    _commands.push_back(new UserCommand());
    _commands.push_back(new NoticeCommand());
    _commands.push_back(new JoinCommand());
    _commands.push_back(new PrivateMessageCommand());
    _commands.push_back(new KickCommand());
    _commands.push_back(new ListCommand());
    _commands.push_back(new PartCommand());
    _commands.push_back(new QuitCommand());
    
}

Invoker::~Invoker() {

}

bool Invoker::isCommand(std::string data)
{
    std::vector<Command *>::iterator it;
    
    for (it = _commands.begin(); it !=_commands.end(); it++)
    {
        //std::cout << "Girdi" << std::endl;
        if((*it)->getName() == data)
            return true;

       
    }
     return false;
}

void Invoker::processCommand(User *sender, std::deque<std::string> args)
{
    
    std::string commandName = args[0];
    //std::cout << "*" << _commands[0]->getName() << "*" << std::endl;

    for (size_t i = 0; i < _commands.size(); i++) {
		if (commandName == _commands[i]->getName()) {
            //std::cout << "İçerideyim";
			_commands[i]->setServer(_server);
			_commands[i]->setSender(sender);
			_commands[i]->setArgs(args);
            try
            {
                _commands[i]->execute();
            }
            catch(const char* message)
            {
                sender->getReply(std::string(message));
            }
            catch(std::string message)
            {
                sender->getReply(message);
            }
			break;
		}
	}
}

std::deque<std::string> Invoker::dataToArgs(std::string data)
{
    std::stringstream ssMsg(data);
    std::string av;
    std::deque<std::string> arguments;

    while(getline(ssMsg, av, ' '))
    {
        av.erase(av.find_last_not_of(MSG_DELIMITER) + 1);
		if (!av.empty())
			arguments.push_back(av);
    }
    return arguments;

}

void Invoker::processData(User *sender, std::string data)
{
    std::deque<std::string> arguments = dataToArgs(data);
    isCommand(arguments[0]);
    if(!arguments.empty() && isCommand(arguments[0]))
    {
        std::cout << "@" << sender->getName() << " " << data;
        //std::cout << "Tam olarak burasi" << sender->getName() << " " << data; // delete
		processCommand(sender, arguments);
    }
    
}

