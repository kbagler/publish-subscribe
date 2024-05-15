#ifndef CONTROLLERTEST_H
#define CONTROLLERTEST_H

#include <gtest/gtest.h>
#include <memory>

#include "Controller.h"
#include "ClientMock.h"

class ControllerTest : public ::testing::Test
{
public:
	ControllerTest() { }
	virtual ~ControllerTest() { }

	void SetUp();

protected:
	std::shared_ptr<ClientMock> client;
	Controller::Ptr controller;

};

#endif /* CONTROLLERTEST_H */

