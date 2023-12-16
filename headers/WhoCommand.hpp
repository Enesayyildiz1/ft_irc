#ifndef WhoCommand_hpp
# define WhoCommand_hpp
# include "../headers/Command.hpp"

class WhoCommand: public Command {
	public:
		WhoCommand();
		virtual ~WhoCommand();
		void execute();
};

#endif