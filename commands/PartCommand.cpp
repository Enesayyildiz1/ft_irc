#include "../headers/PartCommand.hpp"

PartCommand::PartCommand() {
    _name = "PART";
    _description = "PART #channel - leave channel";
}

PartCommand::~PartCommand() {}

void PartCommand::execute() {
    // Kontrol 1: _sender ve _server'ın null olup olmadığını kontrol et
    if (!_sender || !_server) {
        // Eğer nullsa, hata mesajı veya loglama yapabilirsiniz.
        return;
    }

    // Kontrol 2: _sender'ın kayıtlı olup olmadığını kontrol et
    if (!_sender->didRegister()) {
        throw ERR_RESTRICTED;
    }

    // Kontrol 3: _args vektörünün boyutunu kontrol et
    if (_args.size() < 2) {
        throw ERR_NEEDMOREPARAMS(_name);
    }

    // Kontrol 4: _server'tan alınan kanalın null olup olmadığını kontrol et
    Channel *channel = _server->getChannel(_args[1]);
    if (!channel) {
        throw ERR_NOSUCHCHANNEL(_args[1]);
    }

    // Kontrol 5: _sender'ın bu kanalda olup olmadığını kontrol et
    if (_sender->getChannel() != channel) {
        throw ERR_NOTONCHANNEL(_args[1]);
    }

    // Başarılı kontrol durumu
    sendReplyToChannel(channel, _sender->getPrefix() + " " + _name + " #" + channel->getName());
    _sender->removeUserFromChannel();
    _sender->setChannel(nullptr);
}

void PartCommand::sendReplyToChannel(Channel* channel, const std::string& message) const {
    // Kontrol 6: Kanal null değilse devam et
    if (channel) {
        const std::vector<User*>& users = channel->getUsers();

        // Kontrol 7: Kullanıcı vektörünün boş olup olmadığını kontrol et
        if (!users.empty()) {
            for (std::vector<User*>::const_iterator user = users.begin(); user != users.end(); user++) {
                // Kontrol 8: Kullanıcı null değilse mesajı gönder
                if (*user) {
                    (*user)->getReply(message);
                }
            }
        }
    }
}
