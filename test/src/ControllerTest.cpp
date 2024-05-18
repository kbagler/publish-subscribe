#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>

#include "ControllerTest.h"
#include "ClientMock.h"
#include "ViewMock.h"

using namespace testing;

void ControllerTest::SetUp()
{
	client = std::make_shared<ClientMock>();
	input = std::make_shared<InputMock>();
	view = std::make_shared<ViewMock>();

	controller = std::make_unique<Controller>(client, input, view);
}

TEST_F(ControllerTest, CommandFromInputIsExecutedByClient)
{
	EXPECT_CALL(*client, connect("ip:port")).Times(1);
	EXPECT_EQ(input->input("CONNECT ip:port"), 0);

	EXPECT_CALL(*client, disconnect()).Times(1);
	EXPECT_EQ(input->input("DISCONNECT "), 0);

	EXPECT_CALL(*client, publish("topic", "data")).Times(1);
	EXPECT_EQ(input->input("PUBLISH topic data"), 0);

	EXPECT_CALL(*client, subscribe("topic")).Times(1);
	EXPECT_EQ(input->input("SUBSCRIBE topic"), 0);

	EXPECT_CALL(*client, unsubscribe("topic")).Times(1);
	EXPECT_EQ(input->input("UNSUBSCRIBE topic"), 0);
}

TEST_F(ControllerTest, PuttingUnknownCommandReturnsError)
{
	int err = input->input("boo topic data");
	EXPECT_EQ(err, -1);
}

TEST_F(ControllerTest, PublishingEmptyDataIsOk)
{
	EXPECT_CALL(*client, publish(_,_)).Times(4);

	EXPECT_EQ(input->input("PUBLISH topicdata"), 0);
	EXPECT_EQ(input->input("PUBLISH topic_data"), 0);
	EXPECT_EQ(input->input("PUBLISH topic:data"), 0);
	EXPECT_EQ(input->input("PUBLISH topic-data"), 0);
}

TEST_F(ControllerTest, PublishingMultipleWordsInDataIsOk)
{
	EXPECT_CALL(*client, publish("topic", "data moredata evenmoredata")).Times(1);
	EXPECT_EQ(input->input("PUBLISH topic data moredata evenmoredata"), 0);
}

TEST_F(ControllerTest, PublishingEmptyTopicReturnsError)
{
	EXPECT_EQ(input->input("PUBLISH "), -1);
}

TEST_F(ControllerTest, DataReceivedFromClientIsConsumed)
{
	EXPECT_CALL(*view, print_message("topic data")).Times(1);

	EXPECT_EQ(client->receive("topic data"), 0);
}

