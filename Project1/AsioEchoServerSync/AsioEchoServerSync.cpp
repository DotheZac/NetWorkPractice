#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <queue>
#include "Server.h"
#include "Session.h"

//using boost::asio::ip::tcp;
//using namespace std;
//
//class Server;
//
//class Session : public std::enable_shared_from_this<Session>
//{
//public:
//    Session(tcp::socket socket, Server* server)
//        : m_Socket(std::move(socket))
//        , m_pServer(server)
//    {
//    }
//
//    void Start()
//    {
//        SendHello();
//    }
//
//
//    void MySendMessage(char* msg)
//    {
//        auto self = shared_from_this();
//        boost::asio::async_write(
//            m_Socket,
//            boost::asio::buffer(msg, 1024),
//            [this, self](boost::system::error_code ec, std::size_t /*len*/)
//            {
//                if (!ec)
//                {
//
//                }
//            }
//        );
//    }
//
//
//private:
//    void DoRead()
//    {
//        auto self = shared_from_this();
//        m_Socket.async_read_some(
//            boost::asio::buffer(m_Data),
//            [this, self](boost::system::error_code ec, std::size_t length)
//            {
//                if (!ec)
//                {
//                    DoWrite(length);
//                    m_pServer->DoPush(m_Data);
//                    //for (const auto c : m_Data)
//                    //{
//                    //    if (c != '\0')
//                    //        printf("%c", c);
//                    //}
//                    //cout << endl;
//                    memset(m_Data, 0, sizeof(m_Data));
//                }
//                else
//                {
//                    // Client disconnected
//                }
//            }
//        );
//    }
//
//    void DoWrite(std::size_t length)
//    {
//        auto self = shared_from_this();
//        boost::asio::async_write(
//            m_Socket,
//            boost::asio::buffer(m_Data, length),
//            [this, self](boost::system::error_code ec, std::size_t /*len*/)
//            {
//                if (!ec)
//                {
//                    DoRead(); // 계속 읽기
//                }
//            }
//        );
//    }
//
//    void SendHello()
//    {
//        auto self = shared_from_this();
//        boost::asio::async_write(
//            m_Socket,
//            boost::asio::buffer("Hello Client"),
//            [this, self](boost::system::error_code ec, std::size_t /*len*/)
//            {
//                if (!ec)
//                {
//                    DoRead();
//                }
//            }
//        );
//    }
//
//
//    tcp::socket m_Socket;
//    char m_Data[1024] = { '\0', };
//    Server* m_pServer;
//};
//
//
//class Server
//{
//public:
//    Server(boost::asio::io_context& io, uint16_t port)
//        : m_Acceptor(io, tcp::endpoint(tcp::v4(), port))
//    {
//        DoAccept();
//    }
//    void DoPush(char* msg)
//    {
//        m_qMessage.push(msg);
//    }
//
//private:
//    void DoAccept()
//    {
//        m_Acceptor.async_accept(
//            [this](boost::system::error_code ec, tcp::socket socket)
//            {
//                if (!ec)
//                {
//                    auto session = std::make_shared<Session>(std::move(socket), this);
//                    session->Start();
//                    m_vSession.push_back(session);
//                    cout << m_vSession.size() << endl;
//                    //여기서 연결됐다고 회신해보자
//                }
//
//                DoAccept(); // 계속 accept
//            }
//        );
//    }
//
//    void DoSendMessage()
//    {
//        char* msg = m_qMessage.front();
//        for (auto sesseion : m_vSession)
//        {
//            sesseion->MySendMessage(msg);
//        }
//    }
//
//
//    tcp::acceptor m_Acceptor;
//    std::queue<char*> m_qMessage;
//public:
//    std::vector<shared_ptr<Session>> m_vSession;
//
//};


int main()
{
    try
    {
        boost::asio::io_context io;
        Server server(io, 7777);

        std::cout << "[Async Echo] Server listening on port 7777...\n";
        io.run(); // 이벤트 루프 시작
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}
