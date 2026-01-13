#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <queue>


using boost::asio::ip::tcp;
using namespace std;

class Server;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, Server* server)
        : m_Socket(std::move(socket))
        , m_pServer(server)
    {
    }

    void Start()
    {
        SendHello();
    }
    void MySendMessage(char* msg);


private:
    void DoRead();
    void DoWrite(std::size_t length)
    {
        auto self = shared_from_this();
        boost::asio::async_write(
            m_Socket,
            boost::asio::buffer(m_Data, length),
            [this, self](boost::system::error_code ec, std::size_t /*len*/)
            {
                if (!ec)
                {
                    DoRead(); // 계속 읽기
                }
            }
        );
    }

    void SendHello()
    {
        auto self = shared_from_this();
        boost::asio::async_write(
            m_Socket,
            boost::asio::buffer("Hello Client"),
            [this, self](boost::system::error_code ec, std::size_t /*len*/)
            {
                if (!ec)
                {
                    DoRead();
                }
            }
        );
    }


    tcp::socket m_Socket;
    char m_Data[1024] = { '\0', };
    Server* m_pServer;
};
