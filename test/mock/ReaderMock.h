#ifndef READERMOCK_H
#define READERMOCK_H

#include <gmock/gmock.h>

#include "Reader.h"

class ReaderMock : public Reader
{
public:
	ReaderMock() { }
	ReaderMock(const ReaderMock&) = delete;
	ReaderMock(ReaderMock&&) = delete;
	ReaderMock& operator=(const ReaderMock&) = delete;
	ReaderMock& operator=(ReaderMock&&) = delete;
	virtual ~ReaderMock() { }

	int input(const std::string& cmd, unsigned int client_id)
	{
		if (request_handler == nullptr)
			return -1;

		try {
			return request_handler(cmd, client_id);
		} catch (std::bad_function_call &e) {
			return -1;
		}
	}

private:

};

#endif /* READERMOCK_H */

