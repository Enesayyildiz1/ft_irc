#include"headers/User.hpp"
#include "headers/ircserv.hpp"

User::User(int sockfd, char *host, int port)
{
    _nick = "";
    _sockFd = sockfd;
    _host = host;
    _port = port;
    _didEnter = false;
	_channel = nullptr;
    _id = get_id();
}

User::~User(){}

bool 			User::didEnter() const { return _didEnter; }
void			User::setDidEnter(bool value) { _didEnter = value; }
bool			User::didRegister() const { return _didRegister; }
int				User::getSockFd() const { return _sockFd; }
int				User::getPort() const { return _port; }
std::string		User::getName() const { return _nick; }
std::string		User::getHost() const { return _host; }
std::string		User::getNick() const { return _nick; }
std::string		User::getMessage() const { return _message; }
Channel			*User::getChannel() const { return _channel; }
std::string User::getId() const { return _id; }

std::string		User::getSign() const { return _nick + "@" + _host + ":" + std::to_string(_port); }

void			User::setNick(std::string nick) { _nick = nick.substr(0, 9); }
void			User::setUsername(std::string username) { _username = username; }
void			User::setRealname(std::string realname) { _realname = realname; }
void			User::setChannel(Channel *channel) { _channel = channel; }

void User::clearMessage()
{
	_message.clear();
}

void			User::appendMessage(std::string message)
{
	_message.append(message);
	_message.erase(_message.find_last_not_of(MSG_DELIMITER) + 1);
	_message.append("\n");
}

void			User::removeUserFromChannel()
{
	if (_channel != nullptr)
		this->_channel->removeUser(this);
}


std::string User::get_id() {
		std::string s;

		static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
		srand( time( 0 ) ); 
		for (int i = 0; i < 10; ++i) {
			s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		return s;
}

void User::getReply(std::string message)
{
	std::string finalMessage;

	finalMessage = message + MSG_DELIMITER;
	send(_sockFd, finalMessage.c_str(), finalMessage.length(), 0);
}

void	User::sendMessageToUser(User* sender, User* userTo, std::string message) {

	sender->sendMessage(userTo, " #" + this->getName() +  " :" + message + "\r\n");
}

void User::doRegister()
{
	if(_didEnter && _nick != "" && _username != "")
	{
		this->getReply(RPL_WELCOME(_nick, _username, _host));
		_didRegister = true;
	}
}
std::string User::getPrefix() const
{
	return ":" + _nick ;
}

void User::sendMessage(User *to,std::string message)
{
	to->getReply(this->getPrefix() + " " + message);
}