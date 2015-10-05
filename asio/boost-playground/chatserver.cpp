#include "chatserver.h"
#include "chatsession.h"

ChatServer::ChatServer(io_service &ioservice, const tcp::endpoint &endpoint):
    acceptor_(ioservice, endpoint),
    socket_(ioservice)
{
    do_accept();
}

void ChatServer::do_accept()
{
    acceptor_.async_accept(socket_,
                           [this] (boost::system::error_code ec) {
       if (!ec) {
           std::make_shared<ChatSession>(std::move(socket_), chatroom_)->start();
       }
       do_accept();
    });
}

