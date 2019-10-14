#include "ip_filter.h"

#include <gtest/gtest.h>

IPList test_ip_pool = { {"186", "204", "34", "46"}, {"1", "1", "234", "8"} };

TEST(ip_filter_test, ip_filer_test1)
{
	int byte1 = 1;
	auto result = filter(test_ip_pool, [byte1](const IPValue& ip)
	{
		return atoi(ip[0].c_str()) == byte1;
	});

    ASSERT_TRUE(result.size() == 1);
	ASSERT_TRUE(result[0] == IPValue({"1", "1", "234", "8"}));
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}