#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <stdexcept>
#include <signal.h>



void posixDeathSignalAction(int signum)
{

    std::ifstream file("/home/oleg/Documents/ipc_interfaces/ipc_config.json");
    Json::Reader reader;
    Json::Value completeJsonData;
    reader.parse(file, completeJsonData);
    int channel_id = completeJsonData["main_channel_id"].asInt();

    std::cout << "shit happens" << std::endl;
    int m_shmid = shmget(channel_id, 1, IPC_CREAT | 0666);
    shmctl(m_shmid, IPC_RMID, 0);
    std::cout << "tried 2 destroy" << std::endl;

    throw std::invalid_argument("throw after attempt  2 fix error ");

    // signal(signum, SIG_DFL); // перепосылка сигнала
    // exit(3); //выход из программы. Если не сделать этого, то обработчик будет вызываться бесконечно.
}



class IPCInterface
{
public:
    IPCInterface()
    {
        std::ifstream file("/home/oleg/Documents/ipc_interfaces/ipc_config.json");
        Json::Reader reader;
        Json::Value completeJsonData;
        reader.parse(file, completeJsonData);
        this->channel_id = completeJsonData["main_channel_id"].asInt();

        int m_shmid = shmget(this->channel_id, 1, IPC_CREAT | 0666);
        shmctl(m_shmid, IPC_RMID, 0);

    };

    ~IPCInterface();

    template <typename T>
    void sendMsg(T data, int size)
    {
        signal(SIGSEGV, posixDeathSignalAction);

        if(size != this->prev_size)
        {
            std::cout << "NEWshit happens" << std::endl;
            int m_shmid = shmget(this->channel_id, 1, IPC_CREAT | 0666);
            shmctl(m_shmid, IPC_RMID, 0);
            std::cout << "NEWtried 2 destroy" << std::endl;
            this->prev_size = size;
        }

        // try
        {
            int m_shmid = shmget(this->channel_id, size, IPC_CREAT | 0666);
            auto sharedMem = shmat(m_shmid, NULL, 0);
            // T *write_data = new (toWriteNewData) T(data);

            memcpy( sharedMem, data , size );

        }
        // catch (const std::exception &e)
        // {
        //     std::cout << "doin stuff after err";
            
        //     int m_shmid = shmget(this->channel_id, size, IPC_CREAT | 0666);
        //     auto toWriteNewData = shmat(m_shmid, NULL, 0);
        //     T *write_data = new (toWriteNewData) T(data);

        // }
    }

    auto readMsg()
    {
        int m_shmid = shmget(this->channel_id, 1, IPC_CREAT | 0666);
        auto readData = shmat(m_shmid, NULL, 0);
        return readData;
    }

private:
    int channel_id;
    int prev_size;


};
