from python_ipc_interface import IPCInterface
import time, sys


inter = IPCInterface()

s = "sample text" 
a = 123

while 1:
    
    print(int.from_bytes(inter.readMsg(), 'little')) # read variable    
    print(inter.readMsg().decode()) # read str    
    
    
    inter.sendMsg(s.encode('ascii')) # send str
    inter.sendMsg(a.to_bytes(sys.getsizeof(a), 'little')) # send variable
    
    time.sleep(1)
