#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

class Server
{
public:
    Server()
    {
        std::ifstream f("../../../config.json");
        auto data = json::parse(f);
        this->port = data["port"];

        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);

        this->server_address.sin_family = AF_INET;
        this->server_address.sin_addr.s_addr = INADDR_ANY;
        this->server_address.sin_port = htons(this->port);

        bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
        this->nSymbols = data["nSymbols"];
    }

    ~Server();

    void connect()
    {
        listen(this->server_socket, 1);
        socklen_t addrlen = sizeof(client_address);
        this->client_socket = accept(this->server_socket, (struct sockaddr *)&this->client_address, &addrlen);
    }

    void serverJob(void (*onReceive)(char buff[]))
    {
        try
        {
            while (true)
            {
                char buffer[1024] = {0};
                read(this->client_socket, buffer, this->nSymbols);

                if (buffer[0])
                {
                    onReceive(buffer);
                }
                else
                {
                    close(this->client_socket);
                    this->connect();
                    this->serverJob(onReceive);
                }
            }
        }
        catch (const std::exception &e)
        {
            this->connect();
            this->serverJob(onReceive);
        }
    }

    void disconnect()
    {
        close(this->server_socket);
    }

private:
    int port;
    int server_socket;
    struct sockaddr_in server_address;
    int client_socket;
    struct sockaddr_in client_address;
    int nSymbols;
};
