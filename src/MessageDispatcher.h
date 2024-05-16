#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <memory>
#include <string>
#include <unordered_map>

#include "Sender.h"
#include "Message.h"

class MessageDispatcher
{
public:
	using Ptr = std::unique_ptr<MessageDispatcher>;

	MessageDispatcher(Sender::Ptr sndr)
		: sender(sndr) { }

	virtual ~MessageDispatcher() { }

	int subscribe(const std::string& topic, int client_id);
	int unsubscribe(const std::string& topic, int client_id);
	int dispatch(const ServerResponse& msg);

private:
	std::unordered_multimap<std::string, int> subscriptions;
	Sender::Ptr sender;

};

#endif /* MESSAGEDISPATCHER_H */

