#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <boost/asio.hpp>
#include "chatroom.h"

using namespace boost::asio;
using namespace boost::asio::ip;
class ChatServer
{
public:
    ChatServer(io_service& ioservice, const tcp::endpoint& endpoint);

private:
    void do_accept();
private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    ChatRoom chatroom_;
};

#endif // CHATSERVER_H
