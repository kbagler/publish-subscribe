#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>

#include "Reader.h"
#include "Sender.h"
#include "Message.h"

class MessageDispatcher
{
public:
	using Ptr = std::unique_ptr<MessageDispatcher>;

	MessageDispatcher(Reader::Ptr rdr, Sender::Ptr sndr);

	virtual ~MessageDispatcher() { }

	int subscribe(const std::string& topic, unsigned int client_id);
	int unsubscribe(const std::string& topic, unsigned int client_id);
	int unsubscribe(unsigned int client_id);
	int dispatch(const ServerResponse& msg);

private:
	using Command = std::function<int(const std::string&, unsigned int)>;

	int read_request(const std::string& request, unsigned int client_id);
	int handle_request(const std::string& cmd,
			const std::string& data,
			unsigned int client_id);

	std::unordered_map<std::string, Command> cmd_map;
	std::unordered_multimap<std::string, int> subscriptions;
	Reader::Ptr reader;
	Sender::Ptr sender;
	std::mutex command_lock;

};

#endif /* MESSAGEDISPATCHER_H */

