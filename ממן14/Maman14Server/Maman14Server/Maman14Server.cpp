#include "ServerLogic.h"
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

static ServerLogic serverLogic;
static constexpr uint16_t port = 8080;

void listeningOn(boost::asio::io_context&, boost::asio::ip::tcp::endpoint ep)
{
	std::cout << "Listening on " << ep.address() << " port " << ep.port() << "\n";
}

void handleRequest(boost::asio::ip::tcp::socket socket)
{
	try
	{		
		const bool success = serverLogic.handleSocketFromThread(socket);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception in thread: " << ex.what() << std::endl;
	}
}

int main()
{
    std::cout << "Hello Im the server and im alive!!\n";
	try
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(),port);

		boost::asio::io_context ioContext;
		boost::asio::ip::tcp::acceptor accptr(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::loopback(), port));
		listeningOn(ioContext, endpoint);
		while (true)
		{			
			std::thread(handleRequest, accptr.accept()).join();
		}
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Exception: " << ex.what() << std::endl;
	}
}

