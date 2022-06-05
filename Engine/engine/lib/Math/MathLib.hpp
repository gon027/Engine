#pragma once

#include "include/Math.hpp"


#ifdef _DEBUG
#pragma comment(lib, "engine/lib/Math/lib/Debug/MathLib.lib")
#elif 
#pragma comment(lib, "lib/Release/MathLib.lib")
#endif // _DEBUG


using namespace gnLib;