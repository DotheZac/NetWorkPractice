#include "Session.h"
#include "AsioEchoServerSync.h"

void Session::MySendMessage(char* msg)
{
    auto self = shared_from_this();
    boost::asio::async_write(
        m_Socket,
        boost::asio::buffer(msg, 1024),
        [this, self](boost::system::error_code ec, std::size_t /*len*/)
        {
            if (!ec)
            {

            }
        }
    );
}

void Session::DoRead()
{
    auto self = shared_from_this();
    m_Socket.async_read_some(
        boost::asio::buffer(m_Data),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                DoWrite(length);
                m_pServer->DoPush(m_Data);
                //for (const auto c : m_Data)
                //{
                //    if (c != '\0')
                //        printf("%c", c);
                //}
                //cout << endl;
                memset(m_Data, 0, sizeof(m_Data));
            }
            else
            {
                // Client disconnected
            }
        }
    );
}
