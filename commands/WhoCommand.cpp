#include "../headers/WhoCommand.hpp"

WhoCommand::WhoCommand() {
	_name = "WHO";
	_description = "WHO <#channel> - show the list of users on channel";
}

WhoCommand::~WhoCommand() {}

void WhoCommand::execute() {
    // Kontrol: Gönderen kayıt oldu mu?
    if (!_sender->didRegister())
        throw ERR_RESTRICTED;

    // Kontrol: Argüman sayısı doğru mu?
    if (_args.size() != 2)
        throw ERR_NEEDMOREPARAMS(_name);

    // Kanalı al ve kontrol et
    Channel *channel = _server->getChannel(_args[1]);
    if (channel == nullptr)
        throw ERR_NOSUCHCHANNEL(_args[1]);

    // Kanaldaki kullanıcıları al
    std::vector<User*> users = channel->getUsers();

    // Kanal bilgisini ve kullanıcı sayısını gönder
    _sender->getReply("Channel " + channel->getName() + " has " + std::to_string(users.size()) + " users");

    // Kullanıcıları sırayla gönder
    for (const auto& user : users) {
        // Kontrol: Kullanıcı admin mi?
        if (channel->getAdmin() == user)
            _sender->getReply("@" + user->getName());
        else
            _sender->getReply(user->getName());
    }
}
