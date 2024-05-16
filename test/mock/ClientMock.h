#ifndef CLIENTMOCK_H
#define CLIENTMOCK_H

#include <gmock/gmock.h>

#include "Client.h"

class ClientMock : public Client
{
public:
	ClientMock() { }
	virtual ~ClientMock() { }

	MOCK_METHOD(int, connect, (const std::string& ip_port), (override));
	MOCK_METHOD(void, disconnect, (), (override));
	MOCK_METHOD(int, publish, (const std::string& topic, const std::string& data), (override));
	MOCK_METHOD(int, subscribe, (const std::string& topic), (override));
	MOCK_METHOD(int, unsubscribe, (const std::string& topic), (override));

	int receive(const std::string& msg)
	{
		return execute_handler(msg);
	}

private:

};

#endif /* CLIENTMOCK_H */

