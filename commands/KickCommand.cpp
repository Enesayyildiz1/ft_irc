#include "../headers/KickCommand.hpp"

KickCommand::KickCommand() {
	_name = "KICK";
	_description = "KICK <user> <#channel> - kick a user from channel";
}

KickCommand::~KickCommand() {}

void KickCommand::execute() {
    if (!_sender->didRegister())
        throw ERR_RESTRICTED;

    if (_args.size() < 3)
        throw ERR_NEEDMOREPARAMS(_name);

    if (!isAllowedChannelName(_args[2]))
        throw ERR_BADCHANMASK(_args[2]);

    Channel* channel = _server->getChannel(_args[2]);
    if (!channel)
        throw ERR_NOSUCHCHANNEL(_args[2]);

    if (channel->getAdmin() != _sender)
        throw ERR_CHANOPRIVSNEEDED(channel->getName());

    if (!channel->getUser(_sender->getNick()))
        throw ERR_NOTONCHANNEL(channel->getName());

    User* userToKick = channel->getUser(_args[1]);
    if (!userToKick)
        throw ERR_USERNOTINCHANNEL(_args[1], channel->getName());

    channel->sendMessageToChannel(_sender, "Kicked " + userToKick->getName(), _name);
    channel->removeUser(userToKick);
}
