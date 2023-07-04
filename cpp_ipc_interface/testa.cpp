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

    std::string s = "kissing strangers";


    int* i = new int(321);
    while (true)
    {
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
        inter->sendMsg(i, sizeof(i));

        std::cout << "done smth"<<std::endl;
       
        char* data_ = (char*)(inter->readMsg());
        // // read the data from the shared memory
        // char data_got[1024];
        // memcpy(data_got, data_, 1024);
        
            std::cout <<  data_ << ' ';
        

    }
    
}
