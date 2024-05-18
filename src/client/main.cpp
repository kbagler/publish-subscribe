#include <memory>

#include "Controller.h"
#include "ClientConsoleFake.h"
#include "InputConsole.h"
#include "ViewConsole.h"

int main(int argc, char *argv[])
{
	Client::Ptr client = std::make_shared<ClientConsoleFake>();
	InputConsole::Ptr input = std::make_shared<InputConsole>();
	View::Ptr view = std::make_shared<ViewConsole>();

	Controller::Ptr controller = std::make_unique<Controller>(client, input, view);

	input->run();

	return 0;
}

