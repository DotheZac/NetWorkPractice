#include "Server.h"
#include "Session.h"

#include <iostream>

Server::Server(boost::asio::io_context& io, uint16_t port)
    : m_Acceptor(io, tcp::endpoint(tcp::v4(), port))
{
    DoAccept();
}

void Server::DoPush(char* msg)
{
    m_qMessage.push(msg);
    DoSendMessage();
}

void Server::DoAccept()
{
    m_Acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                auto session = std::make_shared<Session>(
                    std::move(socket),
                    this
                );
                session->Start();
                m_vSession.push_back(session);
                std::cout << m_vSession.size() << std::endl;
            }

            DoAccept();
        }
    );
}

void Server::DoSendMessage()
{
    char* msg = m_qMessage.front();
    m_qMessage.pop();

    for (auto sesseion : m_vSession)
    {
        sesseion->MySendMessage(msg);
    }

}