#include "chatsession.h"

using namespace boost::system;

ChatSession::ChatSession(tcp::socket socket, ChatRoom &room):
    socket_(std::move(socket)),
    chat_room_(room)
{

}

void ChatSession::start()
{
    chat_room_.join(shared_from_this());
    do_read_header();
}

void ChatSession::deliver(const ChatMessage &msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
        do_write();
    }
}

void ChatSession::do_read_header()
{
    using namespace boost::asio;
    auto self(shared_from_this());
    async_read(socket_,
               buffer(read_msg_.data(), ChatMessage::header_length),
               [this, self](error_code ec, std::size_t) {
        if (!ec && read_msg_.decode_header()) {
            do_read_body();
        } else {
            chat_room_.leave(shared_from_this());
        }
    });


}

void ChatSession::do_read_body()
{
    using namespace boost::asio;
    auto self(shared_from_this());
    async_read(socket_,
               buffer(read_msg_.body(), read_msg_.body_length()),
            [this, self] (error_code ec, std::size_t) {
        if (!ec) {
            chat_room_.deliver(read_msg_);
            do_read_header();
        } else {
            chat_room_.leave(shared_from_this());
        }
    });

}

void ChatSession::do_write()
{
    using namespace boost::asio;
    auto self(shared_from_this());
    async_write(socket_,
                buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                [this, self] (error_code ec, std::size_t) {
       if (!ec) {
           write_msgs_.pop_front();
           if (!write_msgs_.empty()) {
               do_write();
           }
       } else {
           chat_room_.leave(shared_from_this());
       }
    });

}
