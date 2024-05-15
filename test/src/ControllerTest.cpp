#include "gmock/gmock.h"
#include <gtest/gtest.h>

#include "ControllerTest.h"
#include "ClientMock.h"

using namespace testing;

void ControllerTest::SetUp()
{
	client = std::make_shared<ClientMock>();

	controller = std::make_unique<Controller>(client);
}

TEST_F(ControllerTest, RequestedCommandIsExecutedByClient)
{
	EXPECT_CALL(*client, connect("ip:port")).Times(1);
	EXPECT_EQ(controller->put_command("connect", "ip:port"), 0);

	EXPECT_CALL(*client, disconnect()).Times(1);
	EXPECT_EQ(controller->put_command("disconnect", ""), 0);

	EXPECT_CALL(*client, publish("topic", "data")).Times(1);
	EXPECT_EQ(controller->put_command("publish", "topic data"), 0);

	EXPECT_CALL(*client, subscribe("topic")).Times(1);
	EXPECT_EQ(controller->put_command("subscribe", "topic"), 0);

	EXPECT_CALL(*client, unsubscribe("topic")).Times(1);
	EXPECT_EQ(controller->put_command("unsubscribe", "topic"), 0);
}

TEST_F(ControllerTest, PuttingUnknownCommandReturnsError)
{
	int err = controller->put_command("boo", "topic data");
	EXPECT_EQ(err, -1);
}

TEST_F(ControllerTest, PublishingEmptyDataIsOk)
{
	EXPECT_CALL(*client, publish(_,_)).Times(4);

	EXPECT_EQ(controller->put_command("publish", "topicdata"), 0);
	EXPECT_EQ(controller->put_command("publish", "topic_data"), 0);
	EXPECT_EQ(controller->put_command("publish", "topic:data"), 0);
	EXPECT_EQ(controller->put_command("publish", "topic-data"), 0);
}

TEST_F(ControllerTest, PublishingMultipleWordsInDataIsOk)
{
	EXPECT_CALL(*client, publish("topic", "data moredata evenmoredata")).Times(1);
	EXPECT_EQ(controller->put_command("publish", "topic data moredata evenmoredata"), 0);
}

TEST_F(ControllerTest, PublishingEmptyTopicReturnsError)
{
	EXPECT_EQ(controller->put_command("publish", ""), -1);
}

