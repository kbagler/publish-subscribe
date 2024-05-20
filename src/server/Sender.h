#ifndef SENDER_H
#define SENDER_H

#include <functional>
#include <memory>

class Sender
{
public:
	using Ptr = std::shared_ptr<Sender>;
	using DisconnectHandler = std::function<int(unsigned int)>;

	Sender() { }
	Sender(const Sender&) = delete;
	Sender(Sender&&) = delete;
	Sender& operator=(const Sender&) = delete;
	Sender& operator=(Sender&&) = delete;
	virtual ~Sender() { }

	virtual int send(const std::string& msg, int client_id) = 0;

	void register_disconnect_handler(DisconnectHandler handler)
	{
		disconnect_handler = handler;
	}

protected:
	DisconnectHandler disconnect_handler = nullptr;

private:

};

#endif /* SENDER_H */

