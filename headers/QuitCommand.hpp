#ifndef QUITCOMMAND_HPP
# define QUITCOMMAND_HPP
# include "Command.hpp"



class QuitCommand: public Command {
	public:
		QuitCommand();
		virtual ~QuitCommand();
		void execute();
        void sendReplyToChannel(Channel* channel, std::string message) const ;
};

#endif