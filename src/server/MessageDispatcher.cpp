#include "MessageDispatcher.h"

#include <iostream>
#include <sstream>

#include "Message.h"

/* ----------------------------------------------------------------------------
 * public
 * ------------------------------------------------------------------------- */
MessageDispatcher::MessageDispatcher(Reader::Ptr rdr, Sender::Ptr sndr)
	: reader(rdr), sender(sndr)
{
	cmd_map =
	{
		{"subscribe", [this](const std::string& topic, unsigned int client_id) {
				return this->subscribe(topic, client_id); }},

		{"unsubscribe", [this](const std::string& topic, unsigned int client_id) {
				return this->unsubscribe(topic, client_id); }},

		{"publish", [this](const std::string& topic_data, unsigned int client_id) {
				std::istringstream iss(topic_data);
				std::string topic, data;

				iss >> topic >> std::ws;
				std::getline(iss, data);

				return this->dispatch({topic, data}); }},
	};

	reader->register_request_handler(
			[this](const std::string& request, unsigned int client_id) {
				return this->read_request(request, client_id);
			});

	sender->register_disconnect_handler(
			[this](unsigned int client_id) {
				return this->unsubscribe(client_id);
			});
}

/* ----------------------------------------------------------------------------
 * private
 * ------------------------------------------------------------------------- */
int MessageDispatcher::read_request(const std::string& request,
		unsigned int client_id)
{
	std::istringstream iss(request);
	std::string command, args;

	iss >> command >> std::ws;
	std::getline(iss, args);

	return handle_request(command, args, client_id);
}

int MessageDispatcher::handle_request(const std::string& cmd,
			const std::string& topic_data,
			unsigned int client_id)
{
	auto found = cmd_map.find(cmd);
	if (found == cmd_map.end()) {
		std::cout << "Unknown request: " << cmd << std::endl;
		return -1;
	}

	auto command = std::get<Command>(*found);

	std::lock_guard<std::mutex> lock(command_lock);
	int ret = command(topic_data, client_id);

	return ret;
}

int MessageDispatcher::subscribe(const std::string& topic, unsigned int client_id)
{
	subscriptions.insert({topic, client_id});

	return 0;
}

int MessageDispatcher::unsubscribe(const std::string& topic, unsigned int client_id)
{
	auto subscribers = subscriptions.equal_range(topic);
	for (auto it = subscribers.first; it != subscribers.second; ++it) {
		if (it->second == client_id) {
			subscriptions.erase(it);
			break;
		}
	}

	return 0;
}

int MessageDispatcher::unsubscribe(unsigned int client_id)
{
	for (auto it = subscriptions.begin(); it != subscriptions.end(); )
	{
		if (it->second == client_id)
			it = subscriptions.erase(it);
		else
			++it;
	}

	return 0;
}

int MessageDispatcher::dispatch(const ServerResponse& msg)
{
	auto subscribers = subscriptions.equal_range(msg.topic);
	for (auto it = subscribers.first; it != subscribers.second; ++it)
		sender->send(compose_server_response(msg), it->second);

	return 0;
}

