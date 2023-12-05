#include "headers/Server.hpp"

Server::Server(std::string _port)
{
    this->port = std::atoi(_port.c_str());
    createSocket();
  
}

void Server::createSocket()
{
     // Soket oluşturulması
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Soket oluşturulamadı." << std::endl;

    }

    // Server adresinin tanımlanması
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->port);  // Port numarası

    // Soketin adres ve port numarasına bağlanması
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Bağlanma hatası." << std::endl;
        close(serverSocket);

    }

    // Bekleme moduna geçilmesi
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Bekleme hatası." << std::endl;
        close(serverSocket);

    }

    std::cout << "Sunucu başlatıldı. Bekleniyor..." << std::endl;

    // İstemcilerin kabul edilmesi
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1) {
        std::cerr << "İstemci kabul hatası." << std::endl;
        close(serverSocket);

    }

    std::cout << "İstemci bağlandı." << std::endl;

    // Buradan itibaren KVirc protokolüne özel işlemleri gerçekleştirin.

    // Soketin kapatılması
    close(clientSocket);
    close(serverSocket);
    
}