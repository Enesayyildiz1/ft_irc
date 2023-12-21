#include "../headers/QuitCommand.hpp"

QuitCommand::QuitCommand() {
	_name = "QUIT";
	_description = "QUIT [ <Quit Message> ] —quit server [and leave a message]";
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute() {
	if (_args.size() > 1) {
            _sender->getReply(_args[1]);
	}
    _server->removeUser(_sender->getId());

}
