#include "InputConsole.h"

#include <iostream>

void InputConsole::run()
{
	input_thr = std::thread([this] {
		std::string command;

		while (1) {
			std::cout << ">>> ";
			std::getline(std::cin, command);
			input(command);

			if (command.compare("exit") == 0)
				break;
		}
	});

	if (input_thr.joinable()) {
		input_thr.join();
	}
}

