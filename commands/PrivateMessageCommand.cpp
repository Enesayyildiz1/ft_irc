#include "../headers/PrivateMessageCommand.hpp"

PrivateMessageCommand::PrivateMessageCommand() {
    _name = "PRIVMSG";
    _description = "";
}

PrivateMessageCommand::~PrivateMessageCommand() {}

void PrivateMessageCommand::execute() {
    if (!_sender->didRegister())
        throw ERR_RESTRICTED;

    if (getUserFromArg() != nullptr) {
        User *user = getUserFromArg();
        std::string tmp = makeString();
        if (user && !tmp.empty()) {
            _sender->sendMessageToUser(_sender, user, "PRIVMSG " + user->getNick() + " :" + tmp);
        }

    } else if (getChannelFromArg() != nullptr) {
        Channel *tmp_channel = getChannelFromArg();
        std::string tmp = makeString();
        std::cout << tmp << std::endl;
        if (tmp_channel && !tmp.empty()) {
            tmp_channel->sendMessageToChannel(_sender, tmp, _name);
        }
    } else {
        _sender->getReply("error nick or channel not found");
    }
    clearArg();
}


std::string PrivateMessageCommand::makeString() {
    if (_args.empty()) {
        return "";
    }

    std::stringstream ss;
    ss << _args[0];

    for (size_t i = 1; i < _args.size(); i++) {
        ss << " " << _args[i];
    }

    return ss.str();
}


User *PrivateMessageCommand::getUserFromArg() {
    if (_args.size() < 2) {
        return nullptr;
    }

    std::cout << _args[1];
    User *user = _server->getUser(_args[1]);

    if (user == nullptr) {
        return nullptr;
    }

    return user;
}

void PrivateMessageCommand::clearArg() {
    _args.clear();
}

Channel *PrivateMessageCommand::getChannelFromArg() {
    if (_args.size() < 2) {
        return nullptr;
    }

    std::string getName = _args[1].substr(1);
    return _server->getChannel(getName);
}
