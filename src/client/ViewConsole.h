#ifndef VIEWCONSOLE_H
#define VIEWCONSOLE_H

#include "View.h"

#include <iostream>

class ViewConsole : public View
{
public:
	ViewConsole() { }
	ViewConsole(const ViewConsole&) = delete;
	ViewConsole(ViewConsole&&) = delete;
	ViewConsole& operator=(const ViewConsole&) = delete;
	ViewConsole& operator=(ViewConsole&&) = delete;
	virtual ~ViewConsole() { }

	virtual int print_message(const std::string& msg)
	{
		std::cout << msg << std::endl;
		return 0;
	}

private:

};

#endif /* VIEWCONSOLE_H */

