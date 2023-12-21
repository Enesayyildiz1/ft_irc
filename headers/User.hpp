#ifndef USER_CLASS_HPP
#define USER_CLASS_HPP
#include"libraries.hpp"
#include "../channel/Channel.hpp"
#include<vector>

class Channel;
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
		Channel*			_channel;
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
		void			appendMessage(std::string message);
		std::string getId() const ;
		void			getReply(std::string message);
		void sendMessage(User *to,std::string message);
		void			setChannel(Channel *channel);
		Channel			*getChannel() const;
		void    removeUserFromChannel();
		void	sendMessageToUser(User* sender, User* userTo, std::string message);
        std::string			get_id();
		void clearMessage();
};


#endif