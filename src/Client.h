#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <string>

class Client
{
public:
	using Ptr = std::shared_ptr<Client>;

	Client() { }
	Client(const Client&) = delete;
	Client(Client&&) = delete;
	Client& operator=(const Client&) = delete;
	Client& operator=(Client&&) = delete;
	virtual ~Client() { }

	virtual int connect(const std::string&) = 0;
	virtual void disconnect() = 0;
	virtual int publish(const std::string& topic, const std::string& data) = 0;
	virtual int subscribe(const std::string& topic) = 0;
	virtual int unsubscribe(const std::string& topic) = 0;

private:

};

#endif /* CLIENT_H */

