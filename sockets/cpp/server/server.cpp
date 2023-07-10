#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "json.hpp"
#include <fstream>
#include "server.hpp"


void servJob(char buff[])
{
    std::cout << buff << std::endl;
}


int main()
{
    Server* serv = new Server();
    serv->connect();
    std::cout << "connect!"<< std::endl;
    while(1)
    {
        serv->serverJob(servJob);
    }
    
    return 0;
}
