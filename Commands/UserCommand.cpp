#include "UserCommand.hpp"

// TODO: numeric replies

// Used at the beginning of a connection to specify the user on the server.
// USER <username> <mode> <unused> <realname>

UserCommand::UserCommand(){
    _name = "USER";
    _description = "USER <username> <mode> <unused> <realname> - used at the beginning of connection to specify you on server";
}

UserCommand::~UserCommand() {
}

void UserCommand::execute(){
    if (_args.size() < 4)
        throw ERR_NEEDMOREPARAMS(_name);
    _sender->setUsername(_args[0]);
	_sender->setRealname(_args[3]);
	_sender->doRegister();
}