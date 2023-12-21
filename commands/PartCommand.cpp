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
    _sender->removeUserFromChannel();
    _sender->setChannel(nullptr);
}

