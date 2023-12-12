#include    "HelpCommand.hpp"

// responsible for displaying a list of available commands and their descriptions.

HelpCommand::HelpCommand(): _commands(commands){
    _name = "HELP";
    _description = "HELP - show a list of available commands";
}

HelpCommand::~HelpCommand(){

}

void HelpCommand::execute(){
    _sender->getReply("Commands: "); // Print the header "Commands: ""
    std::vector<Command>::iterator it;
    for (it = _commands.begin(); it != _commands.end(); it++) // iterate through vector of commands
    {
        _sender->getReply((*it))->getDescription()); // retrieve command description send it to sender
    }
}