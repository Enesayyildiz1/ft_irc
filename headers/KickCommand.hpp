#ifndef KICKCOMMAND_HPP
# define KICKCOMMAND_HPP
# include "../headers/Command.hpp"

using namespace std;

class KickCommand: public Command {
	public:
		KickCommand();
		virtual ~KickCommand();
		void execute();
};


#endif