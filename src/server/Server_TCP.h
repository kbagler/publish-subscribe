#ifndef SERVER_TCP_H
#define SERVER_TCP_H

#include "Reader.h"
#include "Sender.h"

#include <asio/error_code.hpp>
#include <asio/thread.hpp>
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
		: socket_(std::move(socket)), receive_callback(rcv) { }

	void start();
	void write(std::string response);

private:
	void do_read();

	ReceiveCallback receive_callback;
	tcp::socket socket_;
	asio::streambuf buffer_;
	std::string rcvd_line_;
};

class Server_TCP : public Reader, public Sender
{
public:
	Server_TCP(asio::io_context& io_context, short port);

	int receive(const std::string& cmd, unsigned int port);

	virtual int send(const std::string& msg, int client_id) override;

private:
	void do_accept();

	tcp::acceptor acceptor_;
	std::unordered_map<unsigned int, Session::Ptr> clients_map;
};

#endif /* SERVER_TCP_H */

