#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include "json.hpp"


using json = nlohmann::json;


class Client
{
    public:
        Client()
        {
            std::ifstream f("../../../config.json");
            auto data = json::parse(f);
            this->port = data["port"];
            this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
        }

        ~Client();

        void connectToServer()
        {
            this->server_address.sin_family = AF_INET;
            this->server_address.sin_port = htons(this->port);
            inet_pton(AF_INET, "127.0.0.1", &this->server_address.sin_addr);
            
            connect(this->client_socket, (struct sockaddr *)&this->server_address, sizeof(this->server_address));
        }

        void sendToServer(const char *message)
        {
            send(this->client_socket, message, strlen(message), 0);
        }

        void disconnect()
        {
            close(this->client_socket);
        }

    
    private:
        int port;
        int server_socket;
        struct sockaddr_in server_address;
        int client_socket;
        struct sockaddr_in client_address;
};