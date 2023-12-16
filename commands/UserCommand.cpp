#include "../headers/UserCommand.hpp"

UserCommand::UserCommand()
{
    _name = "USER";
    _description = "USER <username> <realname>";
}

UserCommand::~UserCommand(){}

void UserCommand::execute()
{
    if(_args.size() < 3)
        throw ERR_NEEDMOREPARAMS(_name);
    _sender->setUsername(_args[1]);
    _sender->setRealname(_args[2]);
    //std::cout << "username: " << _args[1] ;
    //std::cout << "realname: " << _args[2] ;
    _sender->doRegister();
}