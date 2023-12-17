#include "Channel.hpp"

Channel::Channel(std::string name, User* admin, Server *server) :
 _admin(admin), _server(server) {
	setName(name);
}

Channel::~Channel() {}

std::string			Channel::getName()const { return _name; }

User				*Channel::getAdmin()const { return _admin; }

void				Channel::setName(std::string name) {
	size_t maxNameLenght = 200;
	_name = name.substr(1, maxNameLenght);
}

std::vector<User *> Channel::getUsers() const {
	return _users;
}

void				Channel::addUser(User *newUser) {
	_users.push_back(newUser);
}

void	Channel::sendMessageToChannel(User *sender, std::string message, std::string commandName) {
	std::vector<User *>::iterator user;

	for (user = _users.begin(); user != _users.end(); user++) {
		if (*user != sender)
			sender->sendMessage(*user, commandName + " #" + this->getName() +  " :" + message + "\r\n");
	}
}

bool	isAllowedChannelName(std::string channelName) {
	if (channelName.empty()) {
		std::cout << "1";
		return false;
	}
    //std::cout << "channelname:" <<channelName<<"ADAN" ;
	if (channelName[0] != '#' && channelName[0] != '&') {

		return false;
	}

	for (size_t i = 0; i < channelName.size(); i++) {
		if (channelName[i] == ' ' || channelName[i] == 7 || channelName[i] == ',') {
			std::cout << "3";
			return false;
		}
	}
    //std::cout << "Burdayiz baba" << std::endl;
	return true;
}

User			*Channel::getUser(std::string userName)
{
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		std::string	curName = (*itUser)->getName();
		if (curName == userName)
			return *itUser;
	}
	return nullptr;
}

void Channel::removeUser(User *user)
{
    std::vector<User *>::iterator it = std::find(_users.begin(), _users.end(), user);

    if (it != _users.end()) {
        (*it)->setChannel(nullptr);
        _users.erase(it);
    }

    if (_users.empty()) {
        _server->deleteChannel(this);
    }
}