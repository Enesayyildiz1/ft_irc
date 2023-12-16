#ifndef HELPCOMMAND_HPP
#define HELPCOMMAND_HPP
#include "Command.hpp"

class HelpCommand: public Command
{
    private:
        std::vector<Command*>& _commands;
    public:
        HelpCommand(std::vector<Command*>& commands);
        virtual ~HelpCommand();
        void execute();
};

#endif