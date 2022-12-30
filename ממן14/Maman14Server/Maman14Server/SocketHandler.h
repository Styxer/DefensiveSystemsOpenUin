#pragma once
#include <boost/asio/ip/tcp.hpp>

class SocketHandler {

#define PACKET_SIZE  1024

public:
	bool receive(boost::asio::ip::tcp::socket& socket, uint8_t(&buffer)[PACKET_SIZE]);
	bool send(boost::asio::ip::tcp::socket& socket, const uint8_t(&buffer)[PACKET_SIZE]);
};


