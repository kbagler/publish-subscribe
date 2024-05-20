#include "Server_TCP.h"

#include <iostream>

Server_TCP::Server_TCP(asio::io_context& io_context, short port)
	: acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
	do_accept();
}

int Server_TCP::receive(const std::string& cmd, unsigned int port)
{
	return request_handler(cmd, port);
}

int Server_TCP::send(const std::string& msg, int client_id)
{
	auto client = clients_map.find(client_id);
	if (client != clients_map.end()) {
		std::cout << "sending :" << msg << " to client " << client_id << std::endl;
		auto session = std::get<Session::Ptr>(*client);
		session->write(msg + "\n");
	}

	return 0;
}

void Server_TCP::do_accept()
{
	acceptor_.async_accept([this](std::error_code ec, tcp::socket socket) {
			if (!ec) {
				unsigned int port_connected = socket.remote_endpoint().port();
				std::cout << "connected client: "
					<< socket.remote_endpoint().address().to_string()
					<< ":" << port_connected << std::endl;

				Session::Ptr session;
				session = std::make_shared<Session>(std::move(socket),
						[this](const std::string& cmd, unsigned int port) {
							return receive(cmd, port);
						});
				clients_map.insert({port_connected, session});
				session->start();
			}

			do_accept();
		});
}

void Session::start()
{
	asio::thread t([this]() { do_read(); });
}

void Session::write(std::string response)
{
	auto self(shared_from_this());
	asio::async_write(socket_, asio::buffer(response.data(), response.size()),
			[this, self](std::error_code ec, std::size_t /*length*/) {
				if (!ec) {
				}
			});
}

void Session::do_read()
{
	auto self(shared_from_this());
	asio::async_read_until(socket_, buffer_, "\n",
			[this, self](std::error_code ec, std::size_t length) {
				unsigned int port = socket_.remote_endpoint().port();

				if (!ec) {
					asio::streambuf::const_buffers_type bufs = buffer_.data();
					rcvd_line_ = std::string(
							asio::buffers_begin(bufs),
							asio::buffers_begin(bufs) + bufs.size() - 1);

					buffer_.consume(buffer_.size());
					std::cout << "received: " << rcvd_line_
						<< " from client " << port << std::endl;

					receive_callback(rcvd_line_, port);
				} else if (ec == asio::error::eof) {
					std::cout << "client " << port
						<< " closed connection" << std::endl;
				}

			do_read();
		});
}

