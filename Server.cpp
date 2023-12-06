#include "headers/Server.hpp"
#include "headers/error.hpp"
#include "headers/libraries.hpp"

Server::Server(std::string _port)
{
    this->port = std::atoi(_port.c_str());
    createSocket();
  
}

void Server::createSocket()
{
   
    sockaddr_in serverAddress, clientAddress;
    socklen_t clientAddrLen = sizeof(clientAddress);

    // Socket oluşturma
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");

    }

    // Server adresinin tanımlanması
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->port);  // Örnek bir port numarası

    // Soketin adres ve port numarasına bağlanması
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Binding error");
        close(serverSocket);

    }

    // Bekleme moduna geçilmesi
    if (listen(serverSocket, 1) == -1) {
        perror("Listen error");
        close(serverSocket);
 
    }

    std::cout << "Server listening on port" << this->port << std::endl;

    // İstemci bağlantısını kabul etme
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddrLen);
    if (clientSocket == -1) {
        perror("Accept error");
        close(serverSocket);

    }

    std::cout << "Client connected" << std::endl;



    char buffer[256];
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("Read error");
        close(clientSocket);
        close(serverSocket);

    }

    // Ping mesajını yazdırma
    std::cout << "Received ping from client: " << buffer << std::endl;

    // Pong mesajını gönderme
    const char* pongMessage = "pong";
    ssize_t bytesSent = write(clientSocket, pongMessage, strlen(pongMessage));
    if (bytesSent == -1) {
        perror("Write error");
    }

    // Soketleri kapatma
    close(clientSocket);
    close(serverSocket);
}
