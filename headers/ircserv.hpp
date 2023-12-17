#pragma once


#define MSG_DELIMITER "\r\n"
# define ERR_ALREADYREGISTERED					"462 * :Unauthorized command (already registered)"
# define ERR_NEEDMOREPARAMS(command)			("461 * " + command + ": Not enough parameters");
# define ERR_PASSWDMISMATCH						"464 * :Password incorrect"
#define RPL_WELCOME(nick, username, host)		"001 * Welcome to the Internet Relay Network " +  nick + "!" + username + "@" + host
# define ERR_NICKNAMEINUSE(nick)				("433 * " + nick + ":Nickname is already in use")

# define ERR_RESTRICTED							"484 * :Your connection is restricted!"
# define ERR_BADCHANMASK(channel)				("476 * #" + channel + ":Bad Channel Mask")
# define ERR_NOSUCHCHANNEL(channel)				("403 * #" + channel + ":No such channel")
# define ERR_CHANOPRIVSNEEDED(channel)			("482 * #" + channel + ":You're not channel operator")
# define ERR_NOTONCHANNEL(channel)				("442 * " + channel + ":You're not on that channel")
# define ERR_USERNOTINCHANNEL(nick, channel)	("441 * " + nick + " #" + channel + ":They aren't on that channel")
# define ERR_ALREADYINCHANNEL(channel)          ("330 * " + " #" + channel + ":You have already join that channel")

#define RPL_LIST(channel, usersCount)			("322 * #" + channel + " " + usersCount)
#define RPL_LISTEND								"323 * :End of LIST"

