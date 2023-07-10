import server


def onRec(text: str):
    if text and len(text):
        print(text)


serv = server.Server()

serv.connect()
serv.serverJob(onRec)
