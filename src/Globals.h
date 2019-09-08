#pragma once
#include "pch.h"

#ifdef _DEBUG
#define LOG(x) {\
	std::cout << "[" << __FILE__ << "][" << __FUNCTION__ << "][Line " << __LINE__ << "] " << (x) << '\n';\
	}
#else
#define LOG(x)
#endif

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================

namespace cn {
	inline float DELTA_X;
	inline float DELTA_Y;
}

//================================================================================================================================
//================================================================================================================================
//================================================================================================================================