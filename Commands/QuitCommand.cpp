#include "QuitCommand.hpp"

QuitCommand::QuitCommand() {
	_name = "QUIT";
	_description = "QUIT [ <Quit Message> ] — quit server [and leave a message]";
}

QuitCommand::~QuitCommand() {}

void QuitCommand::execute() {
	if (_args > 0) {
        // Join the message components into a single string
        std::string quitMessage = _args[0];
        for (size_t i = 1; i < _args.size(); ++i) {
            quitMessage += " " + _args[i];
        }
        // TO DO: broadcast quit message to necessary channels
         std::cout << "Quit message: " << quitMessage << std::endl;
	}
    _server->removeUser(_sender->getId());

}