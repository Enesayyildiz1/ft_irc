#include "../headers/NickCommand.hpp"

NickCommand::NickCommand() {
	_name = "NICK";
	_description = "NICK <nick> - сhange your nickname";
}

NickCommand::~NickCommand() {}

void NickCommand::execute()
{
    if(_args.size() <= 1)
        throw ERR_NEEDMOREPARAMS(_name);
    std::string oldNick = _sender->getNick();
    std::string newNick = _args[1];
    std::cout << "nick:" << newNick;

    if(_server->getUser(newNick))
        throw ERR_NICKNAMEINUSE(newNick);

    //delete
    if(oldNick != "")
        _sender->sendMessage(_sender, "Nick " + newNick.substr(0, 9));

    _sender->setNick(newNick);
	_sender->doRegister();
}




