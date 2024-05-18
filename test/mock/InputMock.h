#ifndef INPUTMOCK_H
#define INPUTMOCK_H

#include <gmock/gmock.h>

#include "Input.h"

class InputMock : public Input
{
public:
	InputMock() { }
	virtual ~InputMock() { }

	int input(const std::string& cmd)
	{
		if (command_handler == nullptr)
			return -1;

		try {
			return command_handler(cmd);
		} catch (std::bad_function_call &e) {
			return -1;
		}
	}

private:

};

#endif /* INPUTMOCK_H */

