#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP
#include "Command.hpp"


class PassCommand: public Command
{
    public:
        PassCommand();
        virtual ~PassCommand();
        void execute();
};

#endif