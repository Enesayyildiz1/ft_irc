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
        if((curPollfd.revents &POLL_IN) == POLL_IN)
        {
            if(curPollfd.fd == _sock)
            {
                this->greeting(acceptUser());
                std::cout << curPollfd.fd << "-" << _sock;
				break ;
            }
            else
            {
                std::vector<User *>::iterator itUser = _users.begin();
                std::advance(itUser, std::distance(_pollfds.begin(),itPollfd)-1);
                ssize_t byteReceived;
                byteReceived = recvMsg(*itUser);
                std::cout << byteReceived;


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
    std::cout << message << " " << byteReceived;
    return (byteReceived);
} 

