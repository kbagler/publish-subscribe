#include <gtest/gtest.h>

#include "Message.h"

TEST(ClientMessageParseTest, EmptyMessageHasEmptyMembers)
{
	ClientCommand m = parse_client_command("");

	EXPECT_EQ(m.command, "");
	EXPECT_EQ(m.topic, "");
	EXPECT_EQ(m.data, "");
}

TEST(ClientMessageParseTest, MessageMembersAreSpaceDelimited)
{
	std::string msg_single_data = "command topic data";
	ClientCommand m = parse_client_command(msg_single_data);

	EXPECT_EQ(m.command, "command");
	EXPECT_EQ(m.topic, "topic");
	EXPECT_EQ(m.data, "data");

	std::string msg_multiple_data = "command topic data moredata even more data";
	m = parse_client_command(msg_multiple_data);

	EXPECT_EQ(m.command, "command");
	EXPECT_EQ(m.topic, "topic");
	EXPECT_EQ(m.data, "data moredata even more data");
}

