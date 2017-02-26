#include <iostream>
#include <vector>
#include <atomic>
#include <gtest/gtest.h>
#include "../parallel_async.h"
#include "../task.h"

class ConsumerProducerTest : testing::Test { };

TEST(ConsumerProducerTest, Test1)
{
	const size_t N = 1e4;
	std::atomic<size_t> f;
	f = 0;
	asyncply::parallel(
		[&]()
		{
			for (size_t i = 0; i < (N + 1); ++i)
			{
				f += i;
			}
		},
		[&]()
		{
			for (size_t i = 0; i < N; ++i)
			{
				f -= i;
			}
		});
	ASSERT_EQ(f, N);
}

