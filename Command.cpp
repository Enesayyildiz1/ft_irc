# include "Command.hpp"

Command::Command: _name(""), _description(""), _server(NULL), _sender(NULL)
{

}

~Command(){

}

Command:: getName()
{
    return _name;
}

Command:: getDescription()
{
    return _description;
}

Command::setSender(User* sender)
{
    _sender = sender;
}

Command::setServer(Server* server)
{
    _server = server;
}

void setArgs(deque<string> args)
{
    _args = args;
}