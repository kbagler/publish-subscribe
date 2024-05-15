#include "Controller.h"
#include <sstream>

Controller::Controller(Client::Ptr clnt)
	: client(clnt)
{
	cmd_map =
	{
		{"connect", [this](const std::string& server) {
				return client->connect(server); }},

		{"disconnect", [this](const std::string& args) {
				client->disconnect();
				return 0; }},

		{"publish", [this](const std::string& topic_data) {
				std::istringstream iss(topic_data);
				std::string topic, data;

				/* use std::ws to discard whitespace leading before 'data' part */
				iss >> topic >> std::ws;

				/* topic can not be empty */
				if (topic.size() == 0)
					return -1;

				/* put the remainder of the stream to 'data' */
				std::getline(iss, data);

				return client->publish(topic, data); }},

		{"subscribe", [this](const std::string& topic) {
				return client->subscribe(topic); }},

		{"unsubscribe", [this](const std::string& topic) {
				return client->unsubscribe(topic); }},
	};
}

int Controller::put_command(const std::string& cmd, const std::string args)
{
	auto found = cmd_map.find(cmd);
	if (found == cmd_map.end())
		return -1;

	auto command = std::get<Command>(*found);
	int ret = command(args);

	return ret;
}

