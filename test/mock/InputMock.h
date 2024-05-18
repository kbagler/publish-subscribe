#ifndef INPUTMOCK_H
#define INPUTMOCK_H

#include <gmock/gmock.h>

#include "Input.h"

class InputMock : public Input
{
public:
	InputMock() { }
	virtual ~InputMock() { }

private:

};

#endif /* INPUTMOCK_H */

