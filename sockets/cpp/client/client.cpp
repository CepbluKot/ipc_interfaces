#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <fstream>
#include "json.hpp"
#include <unistd.h>
#include<chrono>
#include<thread>
#include "client.hpp"


using json = nlohmann::json;



int main()
{
    Client* cli = new Client();
    cli->connectToServer();
    while(1)
    {
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        cli->sendToServer("wassup m888");
    }

    return 0;

}