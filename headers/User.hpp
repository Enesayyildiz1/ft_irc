#ifndef USER_CLASS_HPP
#define USER_CLASS_HPP
#include"libraries.hpp"
class User
{
    private:
        std::string				_id;
		bool				_didEnter;
		bool				_didRegister;
		int					_sockFd;
		int					_port;
		std::string				_host;
		std::string				_nick;
		std::string				_username;
		std::string				_realname;
		std::string				_message;
    public:
        User(int sockFd, char *host, int port);
        ~User();
        bool			didEnter() const;
		void			setDidEnter(bool value);
		bool			didRegister() const;
		void			doRegister();
		int				getSockFd() const;
		int				getPort() const;
		std::string		getNick() const;
		std::string		getHost() const;
		std::string		getMessage() const;
		std::string		getSign() const;
		std::string		getName() const;
		std::string			getPrefix() const;
		void			setNick(std::string nickname);
		void			setUsername(std::string username);
		void			setRealname(std::string realname);
        std::string			get_id();
};


#endif