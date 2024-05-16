#include "Client.h"

/* ----------------------------------------------------------------------------
 * public
 * ------------------------------------------------------------------------- */
void Client::register_message_handler(MessageHandler handler)
{
	message_handler = handler;
}

/* ----------------------------------------------------------------------------
 * private
 * ------------------------------------------------------------------------- */
int Client::execute_handler(const std::string& msg)
{
	if (message_handler == nullptr)
		return -1;

	try {
		return message_handler(msg);
	} catch (std::bad_function_call &e) {
		return -1;
	}
}

