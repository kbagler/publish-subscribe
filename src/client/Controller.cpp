#include "Controller.h"

#include <sstream>
#include <algorithm>

/* ----------------------------------------------------------------------------
 * public
 * ------------------------------------------------------------------------- */
Controller::Controller(Client::Ptr clnt, Input::Ptr in, View::Ptr vw)
	: client(clnt),
	  input(in),
	  view(vw)
{
	cmd_map =
	{
		{"connect", [this](const std::string& server) {
				return this->connect(server); }},

		{"disconnect", [this](const std::string& args) {
				return this->disconnect(args); }},

		{"publish", [this](const std::string& topic_data) {
				return this->publish(topic_data); }},

		{"subscribe", [this](const std::string& topic) {
				return this->subscribe(topic); }},

		{"unsubscribe", [this](const std::string& topic) {
				return this->unsubscribe(topic); }},
	};

	input->register_command_input([this](const std::string& cmd) {
				return command_handler(cmd); });

	client->register_message_handler([this](const std::string& msg) {
				return message_handler(msg); });
}

/* ----------------------------------------------------------------------------
 * private
 * ------------------------------------------------------------------------- */
int Controller::put_command(const std::string& cmd, const std::string& args)
{
	auto found = cmd_map.find(cmd);
	if (found == cmd_map.end()) {
		view->print_error("unknown command: " + cmd);
		return -1;
	}

	auto command = std::get<Command>(*found);
	int ret = command(args);

	return ret;
}

int Controller::connect(const std::string& server)
{
	return client->connect(server);
}

int Controller::disconnect(const std::string&)
{
	client->disconnect();
	return 0;
}

int Controller::publish(const std::string& topic_data)
{
	std::istringstream iss(topic_data);
	std::string topic, data;

	/* use std::ws to discard whitespace leading before 'data' part */
	iss >> topic >> std::ws;

	/* topic can not be empty */
	if (topic.size() == 0)
		return -1;

	/* put the remainder of the stream to 'data' */
	std::getline(iss, data);

	return client->publish(topic, data);
}

int Controller::subscribe(const std::string& topic)
{
	return client->subscribe(topic);
}

int Controller::unsubscribe(const std::string& topic)
{
	return client->unsubscribe(topic);
}

int Controller::command_handler(const std::string& cmd)
{
	std::istringstream iss(cmd);
	std::string command, args;

	iss >> command >> std::ws;
	std::getline(iss, args);

	/* convert input commands to lower case */
	std::transform(command.cbegin(), command.cend(), command.begin(), ::tolower);

	return put_command(command, args);
}

int Controller::message_handler(const std::string& msg)
{
	return view->print_message(msg);
}

