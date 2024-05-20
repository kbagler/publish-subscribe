#ifndef VIEWMOCK_H
#define VIEWMOCK_H

#include <gmock/gmock.h>

#include "View.h"

class ViewMock : public View
{
public:
	ViewMock() { }
	virtual ~ViewMock() { }

	MOCK_METHOD(int, print_message, (const std::string&), (override));
	MOCK_METHOD(int, print_error, (const std::string&), (override));

private:

};

#endif /* VIEWMOCK_H */

