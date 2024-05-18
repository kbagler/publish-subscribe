#ifndef INPUTCONSOLE_H
#define INPUTCONSOLE_H

#include "Input.h"

#include <thread>

class InputConsole : public Input
{
public:
	using Ptr = std::shared_ptr<InputConsole>;

	InputConsole() { }
	InputConsole(const InputConsole&) = delete;
	InputConsole(InputConsole&&) = delete;
	InputConsole& operator=(const InputConsole&) = delete;
	InputConsole& operator=(InputConsole&&) = delete;
	virtual ~InputConsole() { }

	void run();

private:
	std::thread input_thr;

};

#endif /* INPUTCONSOLE_H */

