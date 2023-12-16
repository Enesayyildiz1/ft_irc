#ifndef PRIVATEMESSAGECOMMAND_HPP
#define PRIVATEMESSAGECOMMAND_HPP

#include"Command.hpp"


class PrivateMessageCommand : public Command
{
    public:
        PrivateMessageCommand();
		virtual ~PrivateMessageCommand();
		void execute();

        std::string makeString();
		User * getUserFromArg();
		Channel * getChannelFromArg();
		void clearArg();
};



#endif