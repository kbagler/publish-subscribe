#ifndef CONTROLLERTEST_H
#define CONTROLLERTEST_H

#include <gtest/gtest.h>
#include <memory>

#include "Controller.h"
#include "ClientMock.h"
#include "InputMock.h"
#include "ViewMock.h"

class ControllerTest : public ::testing::Test
{
public:
	ControllerTest() { }
	virtual ~ControllerTest() { }

	void SetUp();

protected:
	std::shared_ptr<ClientMock> client;
	std::shared_ptr<InputMock> input;
	std::shared_ptr<ViewMock> view;
	Controller::Ptr controller;

};

#endif /* CONTROLLERTEST_H */

