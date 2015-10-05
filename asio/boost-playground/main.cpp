#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include "chatserver.h"

using namespace boost::asio::ip;
using namespace std;
boost::asio::io_service ioservice;


int main()
{
    cout << "Hello World!" << endl;

    tcp::endpoint endpoint(tcp::v4(), 2015);
    ChatServer server(ioservice, endpoint);
    ioservice.run();

    return 0;
}

