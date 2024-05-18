#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <string>

class View
{
public:
	using Ptr = std::shared_ptr<View>;

	View() { }
	View(const View&) = delete;
	View(View&&) = delete;
	View& operator=(const View&) = delete;
	View& operator=(View&&) = delete;
	virtual ~View() { }

	virtual int print_message(const std::string& msg) = 0;

private:

};

#endif /* VIEW_H */

