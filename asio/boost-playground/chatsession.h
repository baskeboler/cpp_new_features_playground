#ifndef CHATSESSION_H
#define CHATSESSION_H
#include <boost/asio.hpp>
#include "chatroom.h"

using namespace boost::asio::ip;

class ChatSession: public ChatParticipant,
        public std::enable_shared_from_this<ChatSession>
{
public:
    ChatSession(tcp::socket socket, ChatRoom& room);
    void start();

    // ChatParticipant interface
public:
    virtual void deliver(const ChatMessage &msg);

private:
    void do_read_header();
    void do_read_body();
    void do_write();

    tcp::socket socket_;
    ChatRoom& chat_room_;
    ChatMessage read_msg_;
    ChatMessageQueue write_msgs_;
};

#endif // CHATSESSION_H
