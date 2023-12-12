#include "NickCommand.hpp"

NickCommand::NickCommand() {
    _name = "NICK";
    _description = "NICK <nick> - сhange your nickname";
}

NickCommand::~NickCommand(){}

bool NickCommand::isNickCharAllowed(char c) {
    return (std::isalnum(c) || c == '[' || c == ']' || c == '\\' || c == '`' ||
            c == '^' || c == '{' || c == '}' || c == '-');
}

void NickCommand::execute(){
    if (_args.size() < 1) // throw an error if a new nickname is not provided
		throw ERR_NEEDMOREPARAMS(_name);

	for (char c : nick) { // Check if all the chars in the nick are valid
        if (!isNickCharAllowed(c)) {
            throw ERR_ERRONEUSNICKNAME(newNick);
        }
    }

	string oldNick = _sender->getNick();
	string newNick = _args[0];

	if (_server->getUser(newNick)) // check if the new nickname is already in use
		throw ERR_NICKNAMEINUSE(newNick);

	if (oldNick != "") { // check if the user had a previous nickname
		_sender->sendMessage(_sender, "NICK " + newNick.substr(0, 9)); // handle change in nickname
	}
	_sender->setNick(newNick);
	_sender->doRegister();
}