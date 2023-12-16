#include "../headers/PartCommand.hpp"

PartCommand::PartCommand() {
	_name = "PART";
	_description = "PART #channel - leave channel";
}

PartCommand::~PartCommand() {}

void PartCommand::execute() {

	if (!_sender->didRegister())
		throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);

	Channel *channel = _server->getChannel(_args[1]);
	if (!channel)
		throw ERR_NOSUCHCHANNEL(_args[1]);
	if (_sender->getChannel() != channel)
		throw ERR_NOTONCHANNEL(_args[1]);

	sendReplyToChannel(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
	_sender->removeUserFromChannel();
	_sender->setChannel(nullptr);
}

void PartCommand::sendReplyToChannel(Channel* channel, std::string message) const {
	std::vector<User *>::iterator	user;
	std::vector<User *>				users = channel->getUsers();

	for (user = users.begin(); user != users.end(); user++) {
		(*user)->getReply(message);
	}
}