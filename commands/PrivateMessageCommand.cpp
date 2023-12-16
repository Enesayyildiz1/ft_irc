#include "../headers/PrivateMessageCommand.hpp"

PrivateMessageCommand::PrivateMessageCommand() {
	_name = "PRIVMSG";
	_description = "";
}

PrivateMessageCommand::~PrivateMessageCommand() {}

void PrivateMessageCommand::execute() {
	if (!_sender->didRegister())
		throw ERR_RESTRICTED;

    if (this->getUserFromArg() != nullptr) {
        User* user = this->getUserFromArg();
        std::string tmp;
        tmp = this->makeString();
        //std::cout << tmp << std::endl;
        //std::cout << "yolucam" << std::endl;
        if (user && !tmp.empty()) {
            _sender->sendMessageToUser(_sender, user,"PRIVMSG " + user->getNick() +  " :"+ this->makeString());
        }
        
    }
    else if (this->getChannelFromArg() != nullptr) {
        Channel* tmp_channel =  this->getChannelFromArg();
        std::string tmp;
        tmp = this->makeString();
        std::cout << tmp << std::endl;
        if (tmp_channel && !tmp.empty()) {
            tmp_channel->sendMessageToChannel(_sender, tmp, this->_name);
        }
    }
    else {
        _sender->getReply("error nick or channel not found");
    }
	this->clearArg();
}

std::string PrivateMessageCommand::makeString() {

    std::string tmp;
    for (size_t i  = 1; i <= _args.size(); i++)
    {
        if (!this->_args[i].empty())
        {
            if (tmp.empty()) {
                tmp =  this->_args[i];
            }
            else {
                tmp = tmp +  " " + this->_args[i];
            }
        }
    }
    tmp.erase(tmp.find_last_not_of(MSG_DELIMITER) + 1);
    return tmp;
}

User *PrivateMessageCommand::getUserFromArg() {
    if (_args.empty()) {
        return nullptr;
    }
    else {
        std::cout << _args[1];
        User* user = _server->getUser(_args[1]);

        if (user == nullptr) {
            return  nullptr;
        }
        else {
            if(user  != nullptr) {
                return  user;
            }
        }
        return nullptr;
    }
}

void PrivateMessageCommand::clearArg() {
    _args.erase(_args.begin(), _args.end());
}

Channel *PrivateMessageCommand::getChannelFromArg() {
    if (_args.empty()) {
        return nullptr;
    }
    else {
        std::string getName = _args[1].substr(1, _args[1].size());

        Channel* channel = _server->getChannel(getName);

        if (channel == nullptr)
        {
            return  nullptr;
        }
        else
        {
            if(channel  != nullptr)
            {

                return  channel;
            }
        }
        return nullptr;
    }
}