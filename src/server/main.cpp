#include <asio.hpp>
#include <memory>
#include <iostream>

#include <getopt.h>

#include "Server_TCP.h"
#include "MessageDispatcher.h"

static const struct option long_options[] = {
	/* Use flags like so:
	{"verbose",	no_argument,	&verbose_flag, 'V'}*/
	/* Argument styles: no_argument, required_argument, optional_argument */
	{"port",                required_argument, nullptr,    'p'},
	{"version",             no_argument,       nullptr,    'v'},
	{"help",                no_argument,       nullptr,    'h'},
	{0, 0, 0, 0}
};
/*no_argument: " "*/
/*required_argument: ":"*/
/*optional_argument: "::" */
const char *optstring = "p:vh";

int port = -1;

static int get_options(int argc, char *argv[]);
static void print_usage(const char *prog_name);

int main(int argc, char* argv[])
{
	get_options(argc, argv);

	try
	{
		asio::io_context io_context;

		std::shared_ptr<Server_TCP> server;
		server = std::make_shared<Server_TCP>(io_context, port);

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

int get_options(int argc, char *argv[])
{
	int choice;

	while (1) {
		int option_index = 0;
		choice = getopt_long( argc, argv,
				optstring,
				long_options, &option_index);

		if (choice == -1)
			break;

		switch (choice) {
		case 'p':
			port = std::stoul(optarg);
			break;

		case 'v':
#ifndef SERVER_VERSION
#define SERVER_VERSION "0.0.0"
#endif
			std::cout << "version: " << SERVER_VERSION << std::endl;

			exit(EXIT_SUCCESS);
			break;

		case 'h':
            print_usage(argv[0]);
			exit(EXIT_SUCCESS);
			break;

		case '?':
			/* getopt_long will have already printed an error */
			/* fallthrough */
		default:
			print_usage(argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (port < 0) {
		std::cerr << "error: server listen port must be set" << std::endl;
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Deal with non-option arguments here */
	if ( optind < argc ) {
	}

	return EXIT_SUCCESS;
}

static void print_usage(const char *prog_name)
{
	std::string pname{basename(prog_name)};
	std::string indent_pname(pname.size() + 1, ' ');

	std::cout << "publish-subscribe server\n"
		<< "\n"
		<< "Usage: \n"
		<< pname << " [-v | --version] [-h | --help]\n"
		<< pname << " [-p | --port=<port>]\n"
		<< "\n";
}

