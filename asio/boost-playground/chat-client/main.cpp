#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "chatclient.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace boost::asio;
int main(int argc, char * argv[])
{
    try {
        if (argc < 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        io_service ioservice;
        tcp::resolver resolver(ioservice);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator iterator = resolver.resolve(query);

        ChatClient c(ioservice, iterator);
        boost::thread t(boost::bind(&io_service::run, &ioservice));

        char line[ChatMessage::max_body_length + 1];
        while (std::cin.getline(line, ChatMessage::max_body_length + 1)) {
            using namespace std;
            ChatMessage msg;
            msg.body_length(strlen(line));
            memcpy(msg.body(), line, msg.body_length());
            msg.encode_header();
            c.write(msg);
        }

        c.close();
        t.join();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}

