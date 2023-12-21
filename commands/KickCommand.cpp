#include "../headers/KickCommand.hpp"

KickCommand::KickCommand() {
	_name = "KICK";
	_description = "KICK <user> <#channel> - kick a user from channel";
}

KickCommand::~KickCommand() {}

void KickCommand::execute() {
    // Kontrol: Gönderen kayıtlı mı?
    if (!_sender->didRegister())
        throw ERR_RESTRICTED;

    // Kontrol: Argüman sayısı doğru mu?
    if (_args.size() < 3)
        throw ERR_NEEDMOREPARAMS(_name);

    // Kontrol: Kanal adı geçerli mi?
    if (!isAllowedChannelName(_args[2]))
        throw ERR_BADCHANMASK(_args[2]);

    // Kanalı al ve kontrol et
    Channel* channel = _server->getChannel(_args[2]);
    if (!channel)
        throw ERR_NOSUCHCHANNEL(_args[2]);

    // Gönderen kanal yöneticisi mi?
    if (channel->getAdmin() != _sender)
        throw ERR_CHANOPRIVSNEEDED(channel->getName());

    // Gönderen kanalda mı?
    if (!channel->getUser(_sender->getNick()))
        throw ERR_NOTONCHANNEL(channel->getName());

    // Kullanıcıyı atılacak kullanıcı olarak al
    User* userToKick = channel->getUser(_args[1]);
    if (!userToKick)
        throw ERR_USERNOTINCHANNEL(_args[1], channel->getName());

    // Kanala mesaj gönder
    channel->sendMessageToChannel(_sender, "Kicked " + userToKick->getName(), _name);

    // Kullanıcıyı kanaldan kaldır
    channel->removeUser(userToKick);
}
