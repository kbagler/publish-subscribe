#ifndef SENDER_H
#define SENDER_H

#include <memory>

class Sender
{
public:
	using Ptr = std::shared_ptr<Sender>;

	Sender() { }
	Sender(const Sender&) = delete;
	Sender(Sender&&) = delete;
	Sender& operator=(const Sender&) = delete;
	Sender& operator=(Sender&&) = delete;
	virtual ~Sender() { }

	virtual int send(const std::string& msg, int client_id) = 0;

private:

};

#endif /* SENDER_H */

