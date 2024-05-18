#include "Input.h"

int Input::input(const std::string& cmd)
{
	if (command_handler == nullptr)
		return -1;

	try {
		return command_handler(cmd);
	} catch (std::bad_function_call &e) {
		return -1;
	}
}

