import sysv_ipc, json, sys


class IPCInterface:
    def __init__(self) -> None:
        config = json.load(open('ipc_config.json'))
        self.main_channel_id = config['main_channel_id']

    def sendMsg(self, data_in_bytes: bytes):
        try:
            size_of_val = len(data_in_bytes)

            memory = sysv_ipc.SharedMemory(self.main_channel_id, mode=0o666, size=size_of_val, flags=sysv_ipc.IPC_CREAT)
            
            if memory.size != size_of_val:
                raise ValueError('memory.size != size_of_val; trying to fix...')
            
            memory.write(data_in_bytes)
            memory.detach()

        except:
            memory_to_remove = sysv_ipc.SharedMemory(self.main_channel_id, mode=0o666, flags=sysv_ipc.IPC_CREAT)
            memory_to_remove.remove()
            self.sendMsg(data_in_bytes)
            
            
    def readMsg(self) -> bytes:
        memory = sysv_ipc.SharedMemory(self.main_channel_id, mode=0o666,  flags=sysv_ipc.IPC_CREAT)
        res = memory.read()
        memory.detach()
        return res
