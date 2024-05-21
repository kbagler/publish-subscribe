#include "ViewConsole.h"

#include <iostream>
#include <sstream>

int ViewConsole::print_message(const std::string& msg)
{
	std::istringstream iss(msg);
	std::string topic, data;

	iss >> topic >> std::ws;
	std::getline(iss, data);

	std::lock_guard<std::mutex> lock(out_lock);
	std::cout << "[Message] Topic: " << topic << " Data: " << data << std::endl;

	return 0;
}

int ViewConsole::print_error(const std::string& msg)
{
	std::cout << "error, " << msg << std::endl;

	return 0;
}

