#include "headers/Server.hpp"
#include "headers/error.hpp"
#include "headers/libraries.hpp"
#include "headers/Invoker.hpp"
#include "headers/ircserv.hpp"

Server::Server(const std::string host, const std::string port, const std::string password): _host(host), _port(port), _password(password)
{
    _sock = createSocket();
    _serverName = _host;
}

void Server::start()
{
    pollfd newPollfd = {_sock, POLLIN, 0};
    if(fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
        throw std::runtime_error("Error: fcntl");
    
    std::vector<pollfd>::iterator it;
    _pollfds.push_back(newPollfd);

    //commandleri handle eden kısım
    _Invoker = new Invoker(this);

    while (true) {

		it = _pollfds.begin();
		if (poll(&(*it), _pollfds.size(), -1) == -1)
			throw std::runtime_error("Error: poll");
        //action fonksiyonunu yapılandır.
        this->action();
        

	}
}

int Server::createSocket()
{
   addrinfo hints;
   addrinfo *servinfo;

   memset(&hints, 0, sizeof(hints));

   hints.ai_family = AF_INET;      // IPv4 kullan
   hints.ai_socktype = SOCK_STREAM;// TCP kullan
   hints.ai_flags = AI_PASSIVE;    // Kendi IP adresini kullan

   if(getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
        throw std::runtime_error("error: getaddrinfo");
    addrinfo *p;
    int sock;
    int yes = 1;

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        // Socket oluştur
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol); //?

        // Socket oluşturma hatası kontrolü
        if (sock == -1)
            continue;

        // SO_REUSEADDR seçeneğini ayarla
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            // Hata durumunda soketi kapat ve servis bilgilerini serbest bırak
            close(sock);
            freeaddrinfo(servinfo);
            throw std::runtime_error("error: setsockopt");
        }

        // Soketi belirtilen adrese bağla
        if (bind(sock, p->ai_addr, p->ai_addrlen) == -1) {
            // Hata durumunda soketi kapat ve bir sonraki adrese geç
            close(sock);
            continue;
        }
        // Başarıyla bağlandıysa döngüden çık
        break;
    }

    freeaddrinfo(servinfo);
    if (p == nullptr)
        throw std::runtime_error("error: failed to find address");

    // Socket'i dinleme moduna al
    if (listen(sock, MAX_CONNECTION) == -1)
        throw std::runtime_error("error: listen");

    // Oluşturulan soketi döndür
    return sock;
}

int Server::acceptUser()
{
    int client_d;
    sockaddr_in client_addr;
    socklen_t s_size;

    s_size = sizeof(client_addr);
    client_d = accept(_sock, (sockaddr*)&client_addr, &s_size);
    if(client_d == -1)
        throw std::runtime_error("error accept");

    pollfd newPollfd ={client_d, POLLIN,0};
    _pollfds.push_back(newPollfd);
    if (fcntl(client_d, F_SETFL, O_NONBLOCK) == -1)
	 	throw std::runtime_error("error fcntl");

    User	*newUser = new User(client_d, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	_users.push_back(newUser);

    std::cout << "New client " << newUser->getName() << "@" << newUser->getHost() << ":" << newUser->getPort() << std::endl;
	return client_d;

    
}

Channel			*Server::getChannel(std::string name)
{
	std::vector<Channel *>::iterator channel;
    std::string tmp = name;
	if (name.empty())
        return nullptr;

    if (tmp.c_str()[0] == '#')
        tmp = tmp.substr(1, tmp.size());
	for (channel = _channels.begin(); channel != _channels.end(); channel++)
	{
		if ((*channel)->getName() == tmp)
			return *channel;
	}
	return nullptr;
}


Channel		*Server::createChannel(std::string name, User *admin)
{
	Channel	*newChannel = new Channel(name, admin, this);
	_channels.push_back(newChannel);
	return newChannel;
}


void			Server::greeting(int client_d)const
{
	std::string str("PASS NICK USER\n\r");
	if (send(client_d, str.c_str(), str.length(), 0) == -1)
		throw std::runtime_error("error send");
}

void Server::action()
{
    pollfd curPollfd;

    for(std::vector<pollfd>::iterator itPollfd = _pollfds.begin(); itPollfd != _pollfds.end(); itPollfd++)
    {
        curPollfd = *itPollfd;
        if ((curPollfd.revents & POLLHUP) == POLLHUP)
        {
            std::vector<User *>::iterator	itUser = _users.begin();
            std::advance(itUser, std::distance(_pollfds.begin(), itPollfd) - 1);

			if (_users.empty())
			{
				break;
			}

            if ((*itUser)->didRegister() && ((*itUser)->getName() != "user_example"))
            {
                std::cout << "disconnect @" << (*itUser)->getName() << std::endl;
                this->removeUser((*itUser)->getId());
            }
            else
            {
                std::cout << "disconnect not registered user" << std::endl;
                this->removeUser((*itUser)->getId());
            }

            break;

        }
        if((curPollfd.revents &POLL_IN) == POLL_IN)
        {
            if(curPollfd.fd == _sock)
            {
                this->greeting(acceptUser());
                //std::cout << curPollfd.fd << "-" << _sock;
				break ;
            }
            else
            {
                std::vector<User *>::iterator itUser = _users.begin();
                std::advance(itUser, std::distance(_pollfds.begin(),itPollfd)-1);
                ssize_t byteReceived;
                byteReceived = recvMsg(*itUser);
                //std::cout << "*" << byteReceived;
                _Invoker->processData(*itUser, (*itUser)->getMessage());

            }
        } 
      
    }
}

int Server::recvMsg(User *user)
{
    ssize_t byteReceived;
    char message[100];

    user->clearMessage();
    memset(message, '\0', sizeof(message));
    while(!std::strstr(message, MSG_DELIMITER))
    {
        memset(message, '\0', sizeof(message));
        byteReceived = recv(user->getSockFd(),message, sizeof(message), 0);
        if(byteReceived <= 0)
            break;
        user->appendMessage(message);
        
        
    }
    return (byteReceived);
} 

bool Server::checkPassword(std::string userPassword)
{
    if(userPassword == _password)
        return true;
    return false;
}

std::string Server::getPrefix() const {
    return ":" + _serverName;
}

void Server::sendMessage(User* to, std::string message)
{
    to->getReply(getPrefix() + " " + message);
}

void			Server::removeUser(std::string id)
{
    std::cout << "id: " << id << " nickname: " << this->getUserById(id)->getNick() << std::endl;
    std::cout << "socket fd: " << this->getUserById(id)->getSockFd() << std::endl;
    this->removeUserFromPoll(id);
    this->removeUserFromUsers(id);
}

void Server::removeUserFromUsers(std::string id) {
	std::vector<User *>::iterator	it = _users.begin();
	std::vector<User *>::iterator	ite = _users.end();
	for (; it != ite; it++ )
	{
		if ((*it)->getId() == id)
		{
            delete (*it);
            _users.erase(it);
            break ;
		}
	}
}

void Server::removeUserFromPoll(std::string id) {
	int socketUser = this->getUserById(id)->getSockFd();
	std::vector<pollfd>::iterator	it = _pollfds.begin();
	std::vector<pollfd>::iterator	ite = _pollfds.end();
	for (; it != ite; it++ )
	{
		if (socketUser == (*it).fd)
		{
			close((*it).fd);
			_pollfds.erase(it);
			break ;
		}
	}
}

User *Server::getUser(std::string name)
{
    for(std::vector<User*>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
    {
        std::string  cur_name = (*itUser)->getName();
        if(cur_name == name)
            return *itUser;
    } 
    return nullptr;
}

User *Server::getUserById(std::string id) {
	for (std::vector<User *>::iterator itUser = _users.begin(); itUser != _users.end(); itUser++)
	{
		std::string	_id = (*itUser)->getId();
		if (_id == id)
			return *itUser;
	}
	return nullptr;
}

std::vector<Channel *> Server::getChannels() { return _channels; }

void	Server::deleteChannel(Channel *channel) {
	std::vector<Channel *>::iterator it;

	for (it = _channels.begin(); it < _channels.end(); it++)
	{
		if (*it == channel)
		{
			_channels.erase(it);
			break ;
		}
	}
}

