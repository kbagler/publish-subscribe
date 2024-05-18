#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "MessageDispatcherTest.h"
#include "SenderMock.h"

using namespace testing;

void MessageDispatcherTest::SetUp()
{
	sender = std::make_shared<SenderMock>();

	dispatcher = std::make_unique<MessageDispatcher>(sender);
}

TEST_F(MessageDispatcherTest, EmptyMessageIsNotSendToAnyone)
{
	EXPECT_CALL(*sender, send(_,_)).Times(0);

	dispatcher->dispatch({"", ""});
}

TEST_F(MessageDispatcherTest, MessageIsSentToSubscriberAfterSubscription)
{
	EXPECT_CALL(*sender, send(_,_)).Times(0);
	dispatcher->dispatch({"topic", "data"});

	dispatcher->subscribe("topic", 0);
	EXPECT_CALL(*sender, send("topic data", 0)).Times(1);
	dispatcher->dispatch({"topic", "data"});
}

TEST_F(MessageDispatcherTest, MessageIsNotSentAfterUnsubscription)
{
	dispatcher->subscribe("topic", 0);
	EXPECT_CALL(*sender, send("topic data", 0)).Times(1);
	dispatcher->dispatch({"topic", "data"});

	dispatcher->unsubscribe("topic", 0);
	EXPECT_CALL(*sender, send("topic data", 0)).Times(0);
	dispatcher->dispatch({"topic", "data"});
}

TEST_F(MessageDispatcherTest, MessageIsSentToMultipleSubscribers)
{
	dispatcher->subscribe("topic", 0);
	dispatcher->subscribe("topic", 1);
	dispatcher->subscribe("topic", 2);
	dispatcher->subscribe("topic", 3);
	dispatcher->subscribe("topic", 4);

	EXPECT_CALL(*sender, send("topic data", 0)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 1)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 2)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 3)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 4)).Times(1);
	dispatcher->dispatch({"topic", "data"});
}

TEST_F(MessageDispatcherTest, MessageIsSentToCorrectSubscribers)
{
	dispatcher->subscribe("topic", 0);
	dispatcher->subscribe("topic", 1);
	dispatcher->subscribe("topic", 2);
	dispatcher->subscribe("topic", 3);
	dispatcher->subscribe("topic", 4);

	dispatcher->unsubscribe("topic", 2);

	EXPECT_CALL(*sender, send("topic data", 0)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 1)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 2)).Times(0);
	EXPECT_CALL(*sender, send("topic data", 3)).Times(1);
	EXPECT_CALL(*sender, send("topic data", 4)).Times(1);
	dispatcher->dispatch({"topic", "data"});
}

