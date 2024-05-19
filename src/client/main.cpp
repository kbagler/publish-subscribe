#include <memory>
#include <asio.hpp>

#include "Controller.h"
#include "Client_TCP.h"
#include "InputConsole.h"
#include "ViewConsole.h"

int main(int argc, char *argv[])
{
	asio::io_context io_context;

	Client::Ptr client = std::make_shared<Client_TCP>(io_context);
	InputConsole::Ptr input = std::make_shared<InputConsole>();
	View::Ptr view = std::make_shared<ViewConsole>();

	Controller::Ptr controller = std::make_unique<Controller>(client, input, view);

    auto work = asio::make_work_guard(io_context);
    std::thread thread([&io_context]() {
				io_context.run();
			});
	input->run();

	io_context.stop();
    thread.join();

	return 0;
}

