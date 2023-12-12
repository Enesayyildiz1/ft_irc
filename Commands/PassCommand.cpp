#include "PassCommand.hpp"

PassCommand::PassCommand() {
	_name = "PASS";
	_description = "PASS <passwordtoserver> - authorise on channel";
}

PassCommand::~PassCommand() {}

void PassCommand::execute() {

	if (_sender->didEnter())
		throw ERR_ALREADYREGISTRED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);

	string password = _args[0]; // retrieve the password
	if (!_server->checkPassword(password)) // check is the provided password matches the expected password
		throw ERR_PASSWDMISMATCH;

	_server->sendMessage(_sender, "PASS Correct password"); // send confirmation to user
	_sender->setDidEnter(true); // marl user as authorized
	_sender->doRegister(); // proceed with the registration
}