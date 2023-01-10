#include "SocketHandler.h"
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <iostream>

/// <summary>
/// recive packet from the socket
/// </summary>
/// <param name="socket">socket to recive from</param>
/// <param name="buffer">an array that the data will be copied to</param>
/// <returns>true is recevied succesfully. false otherwise</returns>
bool SocketHandler::receive(boost::asio::ip::tcp::socket& socket, uint8_t(&buffer)[PACKET_SIZE]) const
{
	bool result = false;
	try 
	{		
		memset(buffer, 0, PACKET_SIZE);
		socket.non_blocking(false);
		boost::asio::read(socket, boost::asio::buffer(buffer, PACKET_SIZE));
		result = true;
	}
	catch (boost::system::system_error& boostErr)
	{
		std::cerr << boostErr.what() << std::endl;
		
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return result;
}

/// <summary>
///  send packet from the socket
/// </summary>
/// <param name="socket">socket to send to</param>
/// <param name="buffer">an array that the data will be read from</param>
/// <returns>true is sent successfully. false otherwise</returns>
bool SocketHandler::send(boost::asio::ip::tcp::socket& socket, const uint8_t(&buffer)[PACKET_SIZE]) const
{
	bool result = false;
	try
	{
		socket.non_blocking(false);
		boost::asio::write(socket, boost::asio::buffer(buffer, PACKET_SIZE));
		result = true;

	}
	catch (boost::system::system_error& boostErr)
	{
		std::cerr << boostErr.what() << std::endl;

	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	return result;
}
