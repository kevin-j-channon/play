#include "CppUnitTest.h"

#include <future>
#include <atomic>
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace play
{
	TEST_CLASS(Threading)
	{
	public:
		
		TEST_METHOD(SimpleAsyncTest)
		{
			auto was_called = false;
			auto f = std::async([&was_called]() {was_called = true; });
			f.get();

			Assert::IsTrue(was_called);
		}

		TEST_METHOD(AsyncWithAtomicStopFlag)
		{
			auto keep_running = std::atomic<bool>{ true };
			auto was_called = false;

			auto f = std::async([&was_called, &keep_running]() {
				while (keep_running);
				was_called = true;
				});

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			keep_running = false;

			f.get();

			Assert::IsTrue(was_called);
		}
	};
}
