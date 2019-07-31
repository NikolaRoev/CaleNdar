#include "pch.h"
#include "CurrentTime.h"


tm current_time() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	time_t tt = std::chrono::system_clock::to_time_t(now);
	
	tm local_tm;
	localtime_s(&local_tm, &tt);

	return local_tm;
}