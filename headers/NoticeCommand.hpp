#ifndef NOTICE_COMMAND_HPP
#define NOTICE_COMMAND_HPP

#include "Command.hpp"

class NoticeCommand: public Command {
	public:
		NoticeCommand();
		virtual ~NoticeCommand();
		void execute();
};

#endif