import client, time


cli = client.Client()

while 1:
    time.sleep(1)
    cli.send("agos2".encode())
    print('sent')
    