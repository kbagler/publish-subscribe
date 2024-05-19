#ifndef CLIENT_TCP_H
#define CLIENT_TCP_H

#include "Client.h"

#include <asio.hpp>

using asio::ip::tcp;

class Client_TCP : public Client
{
public:
	Client_TCP(asio::io_context& io_context);
	virtual ~Client_TCP() { }

	virtual int connect(const std::string& address) override;
	virtual void disconnect() override;
	virtual int publish(const std::string& topic, const std::string& data) override;
	virtual int subscribe(const std::string& topic) override;
	virtual int unsubscribe(const std::string& topic) override;

private:
	tcp::socket socket;
	tcp::resolver resolver;
	asio::streambuf buffer;
	std::string rcvd_line;

	int send_command(const std::string& cmd, const std::string& data);
	void connect_handler(const asio::error_code& ec);
	void do_read();
	int do_write(std::string& msg);

};

#endif /* CLIENT_TCP_H */

