#ifndef QuitCommand_hpp
# define QuitCommand_hpp
# include "../Command.hpp"

using namespace std;

// // TODO: implement leaving channels

class QuitCommand: public Command {
	public:
		QuitCommand();
		virtual ~QuitCommand();
		void execute();
};
#endif