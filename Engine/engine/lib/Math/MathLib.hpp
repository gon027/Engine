#pragma once

#include "include/Math.hpp"


#ifdef _DEBUG
#pragma comment(lib, "engine/lib/Math/lib/Debug/MathLib.lib")
#else 
#pragma comment(lib, "engine/lib/Math/lib/Release/MathLib.lib")
#endif // _DEBUG


using namespace gnLib;