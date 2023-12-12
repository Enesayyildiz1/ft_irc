#ifndef NickCommand_hpp
#define nickCommand_hpp
# include "../Command.hpp"

using namespace std;

class NickCommand: public Command{
    public:
        NickCommand();
        virtual ~NickCommand();
        void execute();
    private:
        bool isNickCharAllowed(char c);
};

#endif