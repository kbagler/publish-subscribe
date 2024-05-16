#ifndef MESSAGEDISPATCHERTEST_H
#define MESSAGEDISPATCHERTEST_H

#include <gtest/gtest.h>

#include "MessageDispatcher.h"
#include "SenderMock.h"

class MessageDispatcherTest : public ::testing::Test
{
public:
	MessageDispatcherTest() { }
	virtual ~MessageDispatcherTest() { }

	void SetUp();

protected:
	std::shared_ptr<SenderMock> sender;
	MessageDispatcher::Ptr dispatcher;

};

#endif /* MESSAGEDISPATCHERTEST_H */

