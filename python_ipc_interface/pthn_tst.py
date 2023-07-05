from python_ipc_interface import IPCInterface
import time

inter = IPCInterface()

while 1:
    resa = inter.readMsg()
    # for b in resa:
    #     print(int(b), end=' ')
    print(int.from_bytes(resa, 'little'))    
    print(resa)
    time.sleep(1)
