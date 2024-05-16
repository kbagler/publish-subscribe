#include "MessageDispatcher.h"
#include "Message.h"

int MessageDispatcher::subscribe(const std::string& topic, int client_id)
{
	subscriptions.insert({topic, client_id});

	return 0;
}

int MessageDispatcher::unsubscribe(const std::string& topic, int client_id)
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

int MessageDispatcher::dispatch(const ServerResponse& msg)
{
	auto subscribers = subscriptions.equal_range(msg.topic);
	for (auto it = subscribers.first; it != subscribers.second; ++it)
		sender->send(compose_server_response(msg), it->second);

	return 0;
}

