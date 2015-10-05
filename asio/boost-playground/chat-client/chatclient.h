#ifndef CHATCLIENT_H
#define CHATCLIENT_H
#include <boost/asio.hpp>
#include "../chatmessage.h"
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::system;
class ChatClient
{
public:
    ChatClient(io_service& ioservice, tcp::resolver::iterator endpoint_iterator);
    void write(const ChatMessage& msg);
    void close();

private:
    void handle_connect(const error_code& error);
    void handle_read_header(const error_code& error);
    void handle_read_body(const error_code& error);
    void do_write(ChatMessage msg);
    void handle_write(const error_code& error);
    void do_close();
private:
    io_service& ioservice_;
    tcp::socket socket_;
    ChatMessage read_msg_;
    ChatMessageQueue write_msgs_;
};

#endif // CHATCLIENT_H
