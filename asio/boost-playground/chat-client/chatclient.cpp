#include "chatclient.h"
#include <boost/bind.hpp>
#include <iostream>

ChatClient::ChatClient(io_service &ioservice, tcp::resolver::iterator endpoint_iterator):
    ioservice_(ioservice),
    socket_(ioservice)
{
    async_connect(socket_,
                  endpoint_iterator,
                  boost::bind(
                      &ChatClient::handle_connect,
                      this,
                      boost::asio::placeholders::error));
}

void ChatClient::write(const ChatMessage &msg)
{
    ioservice_.post(boost::bind(&ChatClient::do_write, this, msg));
}

void ChatClient::close()
{
    ioservice_.post(boost::bind(&ChatClient::do_close, this));
}

void ChatClient::handle_connect(const error_code &error)
{
    if (!error) {
        async_read(socket_, buffer(read_msg_.data(), ChatMessage::header_length),
                   boost::bind(&ChatClient::handle_read_header, this, boost::asio::placeholders::error));
    }
}

void ChatClient::handle_read_header(const error_code &error)
{
    if (!error && read_msg_.decode_header()) {
        async_read(socket_, buffer(read_msg_.body(), read_msg_.body_length()),
                   boost::bind(&ChatClient::handle_read_body, this,
                               boost::asio::placeholders::error));
    } else {
        do_close();
    }
}

void ChatClient::handle_read_body(const error_code &error)
{
    if (!error) {
        std::cout.write(read_msg_.body(), read_msg_.body_length());
        std::cout << std::endl;

        async_read(socket_, buffer(read_msg_.data(), ChatMessage::header_length),
                   boost::bind(&ChatClient::handle_read_header, this,
                               boost::asio::placeholders::error));
    } else {
        do_close();
    }
}

void ChatClient::do_write(ChatMessage msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
    if (!write_in_progress) {
        async_write(socket_, buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                    boost::bind(&ChatClient::handle_write, this,
                                boost::asio::placeholders::error));
    }
}

void ChatClient::handle_write(const error_code &error)
{
    if (!error) {
        write_msgs_.pop_front();
        if (!write_msgs_.empty()) {
            async_write(socket_, buffer(write_msgs_.front().data(), write_msgs_.front().length()),
                        boost::bind(&ChatClient::handle_write, this,
                                    boost::asio::placeholders::error));
        }
    } else {
        do_close();
    }
}

void ChatClient::do_close()
{
    socket_.close();
}

