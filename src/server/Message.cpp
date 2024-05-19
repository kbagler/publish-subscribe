#include "Message.h"

#include <sstream>

ClientCommand parse_client_command(const std::string& msg)
{
	std::istringstream iss(msg);
	std::string command, topic, data;

	iss >> command >> topic >> std::ws;
	std::getline(iss, data);

	return {command, topic, data};
}

std::string compose_server_response(const ServerResponse& msg)
{
	return msg.topic + " " + msg.data + "\n";
}

