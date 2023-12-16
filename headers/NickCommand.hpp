#ifndef NICK_COMMAND_HPP
#define NICK_COMMAND_HPP
#include"Command.hpp"

class NickCommand : public Command{
    public:
            NickCommand();
            virtual ~NickCommand();
            void execute();
};

#endif