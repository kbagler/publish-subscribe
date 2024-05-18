#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

struct ClientCommand {
	std::string command;
	std::string topic;
	std::string data;
};

struct ServerResponse {
	std::string topic;
	std::string data;
};

ClientCommand parse_client_command(const std::string& msg);
std::string compose_server_response(const ServerResponse& msg);

#endif /* MESSAGE_H */

