#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP

#include "Command.hpp"
class UserCommand: public Command
{
    public:
        UserCommand();
        virtual ~UserCommand();
        void execute();
};
#endif