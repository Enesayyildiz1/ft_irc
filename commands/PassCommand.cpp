#include "../headers/PassCommand.hpp"

PassCommand::PassCommand()
{
    _name = "PASS";
    _description = "PASS <passwordtoserver>";
}

PassCommand::~PassCommand() {}

void PassCommand::execute()
{
    if(_sender->didEnter())
        throw ERR_ALREADYREGISTERED;
    if(_args.size() <= 1)
        throw ERR_NEEDMOREPARAMS(_name)

    std::string password = _args[1];
    std::cout << "*" << password << "*";
    if(!_server->checkPassword(password))
        throw ERR_PASSWDMISMATCH;

    _server->sendMessage(_sender, "PASS Correct password");
    _sender->setDidEnter(true);
    _sender->doRegister();
    
}