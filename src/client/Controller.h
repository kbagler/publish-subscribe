#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Client.h"
#include "Input.h"
#include "View.h"

class Controller
{
public:
	using Ptr = std::unique_ptr<Controller>;

	Controller(Client::Ptr clnt, Input::Ptr in, View::Ptr vw);

	Controller(const Controller&) = delete;
	Controller(Controller&&) = delete;
	Controller& operator=(const Controller&) = delete;
	Controller& operator=(Controller&&) = delete;
	virtual ~Controller() { }

private:
	using Command = std::function<int(const std::string&)>;

	Client::Ptr client;
	Input::Ptr input;
	View::Ptr view;
	std::unordered_map<std::string, Command> cmd_map;

	int put_command(const std::string& cmd, const std::string& args);

	int connect(const std::string& server);
	int disconnect(const std::string&);
	int publish(const std::string& topic_data);
	int subscribe(const std::string& topic);
	int unsubscribe(const std::string& topic);

	int command_handler(const std::string& cmd);
	int message_handler(const std::string& msg);

};

#endif /* CONTROLLER_H */

