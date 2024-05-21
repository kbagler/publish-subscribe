#include "Client_TCP.h"

#include <asio.hpp>
#include <asio/buffer.hpp>
#include <iostream>
#include <sstream>

using asio::ip::tcp;

Client_TCP::Client_TCP(asio::io_context& io_context)
	: socket(io_context), resolver(io_context)
{
}

int Client_TCP::connect(const std::string& address)
{
	std::istringstream iss(address);
	std::string ip, port;

	iss >> ip >> port;

	tcp::resolver::iterator iterator
		= resolver.resolve(tcp::resolver::query(ip, port));
	tcp::endpoint endpoint = *iterator;

	socket.async_connect(endpoint,
			[&, this](const asio::error_code& ec) {
				if (!ec) {
					std::cout << "connected to " << ip << " " << port << std::endl;
					connect_handler(ec);
				} else {
					std::cout << "failed connecting to " << ip << " " << port
						<< ": " << ec << std::endl;
				}
			});

	return 0;
}

void Client_TCP::disconnect()
{
    std::error_code ec;
    socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    socket.close();
}

int Client_TCP::publish(const std::string& topic, const std::string& data)
{
	return send_command("publish", topic + " " + data);
}

int Client_TCP::subscribe(const std::string& topic)
{
	return send_command("subscribe", topic);
}

int Client_TCP::unsubscribe(const std::string& topic)
{
	return send_command("unsubscribe", topic);
}

int Client_TCP::send_command(const std::string& cmd, const std::string& data)
{
	std::string command = cmd +" " + data + "\n";
	do_write(command);

	return 0;
}

void Client_TCP::connect_handler(const asio::error_code& ec)
{
	do_read();
}

void Client_TCP::do_read()
{
	asio::async_read_until(socket, buffer, "\n",
			[this](std::error_code ec, std::size_t length) {
				if (!ec) {
					asio::streambuf::const_buffers_type bufs = buffer.data();
					rcvd_line = std::string(
							asio::buffers_begin(bufs),
							asio::buffers_begin(bufs) + bufs.size() - 1);

					buffer.consume(buffer.size());

					execute_handler(rcvd_line);
				}

			do_read();
		});
}

int Client_TCP::do_write(std::string& msg)
{
	asio::async_write(socket, asio::buffer(msg.data(), msg.size()),
			[this](const asio::error_code& error, std::size_t bytes_transferred) {
				if (!error) {
				}
			});

	return 0;
}

