#ifndef VIEWCONSOLE_H
#define VIEWCONSOLE_H

#include "View.h"

#include <mutex>

class ViewConsole : public View
{
public:
	ViewConsole() { }
	ViewConsole(const ViewConsole&) = delete;
	ViewConsole(ViewConsole&&) = delete;
	ViewConsole& operator=(const ViewConsole&) = delete;
	ViewConsole& operator=(ViewConsole&&) = delete;
	virtual ~ViewConsole() { }

	virtual int print_message(const std::string& msg) override;

private:
	std::mutex out_lock;

};

#endif /* VIEWCONSOLE_H */

