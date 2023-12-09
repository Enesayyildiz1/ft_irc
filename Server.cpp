#include "headers/Server.hpp"
#include "headers/error.hpp"
#include "headers/libraries.hpp"
#include "headers/Invoker.hpp"

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

    _Invoker = new Invoker(this);

    while (true) {

		it = _pollfds.begin();
		if (poll(&(*it), _pollfds.size(), -1) == -1)
			throw std::runtime_error("Error: poll");

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
        sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

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
