using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using Newtonsoft.Json;

// Client app is the one sending messages to a Server/listener.
// Both listener and client can send messages back and forth once a
// communication is established.



class Client
{
        class Config
    {
        [JsonProperty("port")]
        public int port { get; set; }

        [JsonProperty("nSymbols")]
        public int nSymbols { get; set; }
    }


    public Client()
    {

        using (StreamReader r = new StreamReader("/home/oleg/Documents/ipc_interfaces/config.json"))
        {
            string json = r.ReadToEnd();
            configs = JsonConvert.DeserializeObject<Config>(json);
        }



        IPHostEntry host = Dns.GetHostEntry("localhost");
        IPAddress ipAddress = host.AddressList[0];
        remoteEP = new IPEndPoint(ipAddress, configs.port);

        // Create a TCP/IP  socket.
        sender = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
    }

    public void connect()
    {
        sender.Connect(remoteEP);
    }

    public void send(byte[] msg)
    {
        try
        {
            sender.Send(msg);
        }
        catch (Exception ex)
        {
        }
    }

    public void disconnect(string msg)
    {
        sender.Shutdown(SocketShutdown.Both);
        sender.Close();
    }
    

    private Socket sender;
    IPEndPoint remoteEP;
    private Config configs;
}



public class SocketClient
{
    public static int Main(String[] args)
    {
        StartClient();
        return 0;
    }

    public static void StartClient()
    {

        Client client = new Client();
        client.connect();
        while(true)
        {
            System.Threading.Thread.Sleep(1000);
            byte[] msg = Encoding.ASCII.GetBytes("sussy amogus");

            client.send(msg);
        }        
    }
}