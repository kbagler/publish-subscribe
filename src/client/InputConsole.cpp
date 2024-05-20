#include "InputConsole.h"

#include <iostream>

void InputConsole::run()
{
	input_thr = std::thread([this] {
		std::string command;

		while (1) {
			std::cout << ">>> ";
			std::getline(std::cin, command);

			if (command.size() == 0)
				continue;

			if (command.compare("exit") == 0)
				break;

			input(command);
		}
	});

	if (input_thr.joinable()) {
		input_thr.join();
	}
}

