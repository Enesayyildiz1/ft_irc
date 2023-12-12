#include "NoticeCommand.hpp"

// Allows a user to send a notice to another user

NoticeCommand::NoticeCommand() {
    _name = "NOTICE";
    _description = "NOTICE username message - sends message to user";
}

NoticeCommand::~NoticeCommand(){

}

void NoticeCommand::execute(){
    if (!_sender->didRegister())
        return ;
    if (_args.size() < 2) // at least target username and the message need to be provided
        return ;
    
    User* user = _server->getUser(_args[0]); // User lookup
    if (!user || user == _sender) // if the user is not found or is same as the sender return
        return ;
    
    string message;
    deque<string>::iterator word;

    for (word = _args.begin() + 1; word != _args.end(); word++)
    {
        message += " " + *word; // concatanate the rest of the arguments to form a single message string
    }
    _sender->sendMessage(user, "NOTICE " + user->getNick() + message); // Send the notice to the target user
}
