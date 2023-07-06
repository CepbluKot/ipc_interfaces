#include <iostream>
#include<chrono>
#include<thread>
#include <string>

#include <cstddef>
#include <cstring>
 
#include "cpp_ipc_interface.h"


int main()
{
    IPCInterface *inter =  new IPCInterface();

    int s =131;
    std::string i = "lolol";
    while (true)
    {
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        inter->sendMsgArr(i.c_str(), i.size ()); // send string

        inter->sendMsgVar(s, sizeof(s)); // send variable

        int* data_ = static_cast<int*>(inter->readMsg()); // read variable
        std::cout << *data_ << std::endl; // print variable
       
        char* data_ = static_cast<char*>(inter->readMsg()); // read char array (str)
        std::cout << data_ << std::endl; // print char array (str)
    }
    
}
