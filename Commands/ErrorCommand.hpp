#ifndef ErrorCommand_hpp
# define ErrorCommand_hpp
# include "../Command.hpp"

using namespace std; // Uasak mı kontrol et

class ErrorCommand: public Command {
    public:
        ErrorCommand();
        virtual ~ErrorCommand();
        void    execute();
};

#endif