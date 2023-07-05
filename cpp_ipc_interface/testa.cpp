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
        
        inter->sendMsgArr(i.c_str(), i.size());

        std::cout << "done smth"<<std::endl;
        inter->sendMsgVar(s, sizeof(s));
        int* data_ = static_cast<int*>(inter->readMsg());
        // // read the data from the shared memory
        // char data_got[1024];
        // memcpy(data_got, data_, 1024);
        
        std::cout <<  *data_ << ' ';
        // reinit mem!
        

    }
    
}
