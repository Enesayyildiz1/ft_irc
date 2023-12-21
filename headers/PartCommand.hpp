#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP
# include "../headers/Command.hpp"



class PartCommand: public Command {
	public:
		PartCommand();
		virtual ~PartCommand();
		void execute();
};

#endif