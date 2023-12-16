#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../headers/libraries.hpp"
#include "../headers/User.hpp"
#include "../headers/Server.hpp"
class Server;
class User;


bool isAllowedChannelName(std::string name);
class Channel
{
    private:
		std::string			_name;
		std::vector<User *>	_users;
		User*				_admin;
		Server*				_server;

    public:
	    Channel(std::string name, User* admin, Server *server);
		~Channel();
        std::string		getName() const;
		User			*getAdmin()const;
        void			setName(std::string name);
        void			addUser(User *newUser);
		std::vector<User *> getUsers() const; 
		User			*getUser(std::string userName);
		void			removeUser(User *user);
		void	sendMessageToChannel(User *sender, std::string message, std::string commandName);
};

#endif