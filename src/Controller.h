#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Client.h"

class Controller
{
public:
	using Ptr = std::unique_ptr<Controller>;

	Controller(Client::Ptr clnt);

	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;
	virtual ~Controller() { }

	virtual int put_command(const std::string& cmd, const std::string args);

private:
	using Command = std::function<int(const std::string&)>;

	Client::Ptr client;
	std::unordered_map<std::string, Command> cmd_map;

	int connect(const std::string& server);
	int disconnect(const std::string&);
	int publish(const std::string& topic_data);
	int subscribe(const std::string& topic);
	int unsubscribe(const std::string& topic);

};

#endif /* CONTROLLER_H */

