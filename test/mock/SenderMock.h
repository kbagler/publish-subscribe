#ifndef SENDERMOCK_H
#define SENDERMOCK_H

#include <gmock/gmock.h>

#include "Sender.h"

class SenderMock : public Sender
{
public:
	SenderMock() { }
	virtual ~SenderMock() { }

	MOCK_METHOD(int, send, (const std::string& msg, int client_id), (override));

	void disconnect(int client_id)
	{
		disconnect_handler(client_id);
	}

private:

};

#endif /* SENDERMOCK_H */

