#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <queue>

using boost::asio::ip::tcp;

class Session; 

class Server
{
public:
    Server(boost::asio::io_context& io, uint16_t port);

    void DoPush(char* msg);

private:
    void DoAccept();
    void DoSendMessage();

private:
    tcp::acceptor m_Acceptor;
    std::queue<char*> m_qMessage;
    std::vector<std::shared_ptr<Session>> m_vSession;
};
