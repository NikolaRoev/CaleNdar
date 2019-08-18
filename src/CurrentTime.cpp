#include "pch.h"
#include "CurrentTime.h"


//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

tm current() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	time_t tt = std::chrono::system_clock::to_time_t(now);
	
	tm local_tm;
	localtime_s(&local_tm, &tt);

	return local_tm;
}

cn::CurrentTime get_current_time() {
	tm temp = current();

	cn::CurrentTime out;

	out.hour = temp.tm_hour;
	out.minute = temp.tm_min;
	out.second = temp.tm_sec;

	return out;
}

cn::CurrentDate get_current_date() {
	tm temp = current();

	cn::CurrentDate out;

	out.year = temp.tm_year + 1900;
	out.month = temp.tm_mon;
	out.day = temp.tm_mday - 1;

	return out;
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================