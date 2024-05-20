#include <iostream>
#include <memory>
#include <asio.hpp>

#include <getopt.h>

#include "Controller.h"
#include "Client_TCP.h"
#include "InputConsole.h"
#include "ViewConsole.h"

static const struct option long_options[] = {
	/* Use flags like so:
	{"verbose",	no_argument,	&verbose_flag, 'V'}*/
	/* Argument styles: no_argument, required_argument, optional_argument */
	{"version",             no_argument,       nullptr,    'v'},
	{"help",                no_argument,       nullptr,    'h'},
	{0, 0, 0, 0}
};
/*no_argument: " "*/
/*required_argument: ":"*/
/*optional_argument: "::" */
const char *optstring = "vh";

static int get_options(int argc, char *argv[]);
static void print_usage(const char *prog_name);

int main(int argc, char *argv[])
{
	get_options(argc, argv);

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
		case 'v':
#ifndef CLIENT_VERSION
#define CLIENT_VERSION "0.0.0"
#endif
			std::cout << "version: " << CLIENT_VERSION << std::endl;

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

	/* Deal with non-option arguments here */
	if ( optind < argc ) {
	}

	return EXIT_SUCCESS;
}

static void print_usage(const char *prog_name)
{
	std::string pname{basename(prog_name)};
	std::string indent_pname(pname.size() + 1, ' ');

	std::cout << "publish-subscribe client\n"
		<< "\n"
		<< "Usage: \n"
		<< pname << " [-v | --version] [-h | --help]\n"
		<< "\n";
}

