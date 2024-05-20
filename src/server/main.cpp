#include <asio.hpp>
#include <memory>
#include <iostream>

#include "Server_TCP.h"
#include "MessageDispatcher.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		asio::io_context io_context;

		std::shared_ptr<Server_TCP> server;
		server = std::make_shared<Server_TCP>(io_context, std::atoi(argv[1]));

		Reader::Ptr reader = server;
		Sender::Ptr sender = server;
		MessageDispatcher::Ptr dispatcher
			= std::make_unique<MessageDispatcher>(reader, sender);

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

