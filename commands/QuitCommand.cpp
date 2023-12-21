#include "../headers/QuitCommand.hpp"

QuitCommand::QuitCommand() {
	_name = "QUIT";
	_description = "QUIT [ <Quit Message> ] —quit server [and leave a message]";
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute() {
	if (_args.size() > 1) {
            //sendReplyToChannel(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
            _sender->getReply(_args[1]);
	}
    _server->removeUser(_sender->getId());

}

void QuitCommand::sendReplyToChannel(Channel* channel, std::string message) const {
	std::vector<User *>::iterator	user;
	std::vector<User *>				users = channel->getUsers();

	for (user = users.begin(); user != users.end(); user++) {
		(*user)->getReply(message);
	}
}