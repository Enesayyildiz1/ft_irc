#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP
# include "Command.hpp"



class JoinCommand: public Command {
	public:
		JoinCommand();
		virtual ~JoinCommand();
		void execute();
		void sendReplyToChannel(Channel* channel, std::string message) const;

};

#endif