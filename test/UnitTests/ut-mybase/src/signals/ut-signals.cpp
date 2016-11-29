#include "precompiled.h"
#include <catch.hpp>
#include <signals/signals.h>


typedef mybase::Signal<void, int> TestEventHandler;

class TestSignalClass {
public:
	TestEventHandler TestEvent;
};

class TestSlotClass {
public:
	void HandleEvent(int i) {
		++m_countOfEventCalls;
		m_sumOfParams += i;
	}

	auto GetSlot() {
		return [&](auto... args) { this->HandleEvent(args...); };
	}

	size_t m_countOfEventCalls = 0;
	size_t m_sumOfParams = 0;
};

TEST_CASE("Signals", "[full]") {
	TestSignalClass signal;
	TestSlotClass slot1;
	TestSlotClass slot2;

	auto slot1_id = signal.TestEvent.Subscribe(slot1.GetSlot());
	auto slot2_id = signal.TestEvent.Subscribe(slot2.GetSlot());

	signal.TestEvent.Emit(10);

	CHECK(slot1.m_countOfEventCalls == 1);
	CHECK(slot2.m_countOfEventCalls == 1);
	CHECK(slot1.m_sumOfParams == 10);
	CHECK(slot2.m_sumOfParams == 10);

	signal.TestEvent.Release(slot2_id);
	signal.TestEvent.Emit(1);

	CHECK(slot1.m_countOfEventCalls == 2);
	CHECK(slot2.m_countOfEventCalls == 1);
	CHECK(slot1.m_sumOfParams == 11);
	CHECK(slot2.m_sumOfParams == 10);
}
	