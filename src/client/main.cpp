#include <iostream>

int main(int argc, char *argv[])
{
	std::string command;

    while (1){
        std::cout << "prompt> ";
        std::getline(std::cin, command);
        std::cout << command << std::endl;
        if (command.compare("exit") == 0) break;
    }

	return 0;
}

