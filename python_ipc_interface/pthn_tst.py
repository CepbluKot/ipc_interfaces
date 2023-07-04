from python_ipc_interface import IPCInterface
import time

inter = IPCInterface()

while 1:
    resa = inter.readMsg()
    # for b in resa:
    #     print(int(b), end=' ')
    print(resa)    
    
    print('\n')
    # inter.sendMsg('abra'.encode())
    print('k')
    time.sleep(1)
