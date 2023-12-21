#include "../headers/PartCommand.hpp"

PartCommand::PartCommand() {
    _name = "PART";
    _description = "PART #channel - leave channel";
}

PartCommand::~PartCommand() {}

void PartCommand::execute() {
    if (!_sender || !_server) {
        return;
    }

    if (!_sender->didRegister()) {
        throw ERR_RESTRICTED;
    }

    if (_args.size() < 2) {
        throw ERR_NEEDMOREPARAMS(_name);
    }

    Channel *channel = _server->getChannel(_args[1]);
    if (!channel) {
        throw ERR_NOSUCHCHANNEL(_args[1]);
    }

    if (_sender->getChannel() != channel) {
        throw ERR_NOTONCHANNEL(_args[1]);
    }
    _sender->removeUserFromChannel();
    _sender->setChannel(nullptr);
}

