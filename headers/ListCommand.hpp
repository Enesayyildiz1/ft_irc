#ifndef LISTCOMMAND_HPP
# define LISTCOMMAND_HPP
# include "../headers/Command.hpp"

using namespace std;

class ListCommand: public Command {
	public:
		ListCommand();
		virtual ~ListCommand();
		void execute();
};

#endif