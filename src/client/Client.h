#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <functional>
#include <string>

class Client
{
public:
	using Ptr = std::shared_ptr<Client>;
	using MessageHandler = std::function<int(const std::string&)>;

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

	void register_message_handler(MessageHandler handler);

protected:
	MessageHandler message_handler = nullptr;

	int execute_handler(const std::string& msg);

};

#endif /* CLIENT_H */

