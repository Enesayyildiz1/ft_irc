#include"headers/User.hpp"

User::User(int sockfd, char *host, int port)
{
    _nick = "";
    _sockFd = sockfd;
    _host = host;
    _port = port;
    _didEnter = false;
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


std::string		User::getSign() const { return _nick + "@" + _host + ":" + std::to_string(_port); }

void			User::setNick(std::string nick) { _nick = nick.substr(0, 9); }
void			User::setUsername(std::string username) { _username = username; }
void			User::setRealname(std::string realname) { _realname = realname; }

std::string User::get_id() {
		std::string s;

		static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
		srand( time( 0 ) ); // автоматическая рандомизация
		for (int i = 0; i < 10; ++i) {
			s += alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		return s;
}