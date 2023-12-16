#include "../headers/JoinCommand.hpp"
#include "../channel/Channel.hpp"


JoinCommand::JoinCommand() {
	 _name = "JOIN";
	 _description = "JOIN <#channel> - join or create a channel";
}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute() {

	if (!_sender->didRegister())
	    throw ERR_RESTRICTED;
	if (_args.size() < 1)
		throw ERR_NEEDMOREPARAMS(_name);
    if (!isAllowedChannelName(_args[1]))
		throw ERR_BADCHANMASK(_args[1]);

	Channel *channel = _server->getChannel(_args[1]);
	if (!channel) {
		channel = _server->createChannel(_args[1], _sender);
        //std::cout << "burada";
	}
	_sender->setChannel(channel);
	channel->addUser(_sender);
	sendReplyToChannel(channel, _sender->getPrefix() + " " + this->_name + " #" + channel->getName());
}

void JoinCommand::sendReplyToChannel(Channel* channel, std::string message) const {
	std::vector<User *>::iterator	user;
	std::vector<User *>				users = channel->getUsers();

	for (user = users.begin(); user != users.end(); user++) {
		(*user)->getReply(message);
	}
}