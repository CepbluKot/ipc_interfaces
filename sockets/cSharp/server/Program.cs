using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

// Socket Listener acts as a server and listens to the incoming
// messages on the specified port and protocol.


class Server
{
    public Server()
    {
        IPHostEntry host = Dns.GetHostEntry("localhost");
        IPAddress ipAddress = host.AddressList[0];
        IPEndPoint localEndPoint = new IPEndPoint(ipAddress, 11000);

        listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        listener.Bind(localEndPoint);
    }


    public void connect()
    {
        listener.Listen(10);
        handler = listener.Accept();
    }

    public void serverJob(Func<string, int> onReceive)
    {
        while (true)
        {
            string data = null;
            byte[] bytes = null;

            bytes = new byte[1024];
            int bytesRec = handler.Receive(bytes);


            if (bytesRec != 0)
            {
                data += Encoding.ASCII.GetString(bytes, 0, bytesRec);
                onReceive(data);
            }
            else
            {
                handler.Shutdown(SocketShutdown.Both);
                this.connect();
            }
        }
    }

    private Socket listener;
    private Socket handler;
}


public class SocketListener
{
    public static int Main(String[] args)
    {
        StartServer();
        return 0;
    }


    public static int dosmth(string wtf)
    {
        Console.WriteLine(wtf);
        return 0;
    }

    public static void StartServer()
    {
        Server server = new Server();
        server.connect();
        server.serverJob(dosmth);
    }
}