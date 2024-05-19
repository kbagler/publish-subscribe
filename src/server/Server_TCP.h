#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include "Reader.h"
#include "Sender.h"

#include <asio/thread.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <asio.hpp>

using asio::ip::tcp;

using ReceiveCallback = std::function<int(const std::string&, unsigned int)>;

class Session : public std::enable_shared_from_this<Session>
{
public:
	using Ptr = std::shared_ptr<Session>;

	Session(tcp::socket socket, ReceiveCallback rcv)
		: socket_(std::move(socket)), receive_callback(rcv)
	{
	}

	void start()
	{
		asio::thread t([this]() { do_read(); });
	}

	void write(std::string response)
	{
		auto self(shared_from_this());
		asio::async_write(socket_, asio::buffer(response.data(), response.size()),
				[this, self](std::error_code ec, std::size_t /*length*/) {
					if (!ec) {
						do_read();
					}
				});
	}

private:
	void do_read()
	{
		auto self(shared_from_this());
		asio::async_read_until(socket_, buffer_, "\n",
				[this, self](std::error_code ec, std::size_t length) {
					if (!ec) {
						asio::streambuf::const_buffers_type bufs = buffer_.data();
						rcvd_line_ = std::string(
								asio::buffers_begin(bufs),
								asio::buffers_begin(bufs) + bufs.size() - 1);

						buffer_.consume(buffer_.size());
					}

				std::cout << "received: " << rcvd_line_
				<< " from client " << socket_.remote_endpoint().port()
				<< std::endl;

				receive_callback(rcvd_line_, socket_.remote_endpoint().port());

				do_read();
			});
	}

	ReceiveCallback receive_callback;
	tcp::socket socket_;
	asio::streambuf buffer_;
	std::string rcvd_line_;
};

class Server_TCP : public Reader, public Sender
{
public:
	Server_TCP(asio::io_context& io_context, short port)
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
	{
		do_accept();
	}

	int receive(const std::string& cmd, unsigned int port)
	{
		return request_handler(cmd, port);
	}

	virtual int send(const std::string& msg, int client_id)
	{
		auto client = clients_map.find(client_id);
		if (client != clients_map.end()) {
			std::cout << "sending :" << msg << " to client " << client_id << std::endl;
			auto session = std::get<Session::Ptr>(*client);
			session->write(msg);
		}

		return 0;
	}

private:
	void do_accept()
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

	tcp::acceptor acceptor_;
	std::unordered_map<unsigned int, Session::Ptr> clients_map;
};

#endif /* SERVER_TCP_H */

/* class ServerTCP : public Reader, public Sender */
/* { */
/* public: */
/* 	ServerTCP(); */
/* 	ServerTCP(const ServerTCP&) = delete; */
/* 	ServerTCP(ServerTCP&&) = delete; */
/* 	ServerTCP& operator=(const ServerTCP&) = delete; */
/* 	ServerTCP& operator=(ServerTCP&&) = delete; */
/* 	virtual ~ServerTCP() { } */

/* private: */

/* }; */
