#include "ServerLogic.h"
#include <iostream>
#include <thread>
#include <boost/asio.hpp>


static ServerLogic serverLogic;
static const uint16_t port = 8080;

void handleRequest(boost::asio::ip::tcp::socket socket)
{
	try
	{
		std::stringstream err;
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
		boost::asio::io_context io_context;
		boost::asio::ip::tcp::acceptor accptr(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
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

