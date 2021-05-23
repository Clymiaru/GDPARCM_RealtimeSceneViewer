#pragma once

#include <iostream>

#ifdef DEBUG
#define ASSERT(expectation, errorMessage)																		\
	if(!(expectation))																							\
	{																											\
		std::cout << errorMessage << " [" << __FUNCSIG__ << " " << __FILE__ << " Line:" << __LINE__ << "]\n\n";	\
		__debugbreak();																							\
	}
#define LOG(message)																						\
	{																										\
		std::cout << message << " [" << __FUNCSIG__ << " " << __FILE__ << " Line:" << __LINE__ << "]\n\n";	\
	}

#else
#define ASSERT(expectation, errorMessage)
#define LOG(message)
#endif
