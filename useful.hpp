#pragma once

/**
 * File containing useful includes, defines, and functions.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4 0.78539816339744830962
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

#ifndef CONVERT_NAMESPACE
#define CONVERT_NAMESPACE
namespace convert {
    // Convert degrees to radians
    static double degToRad(double degrees) {
        return degrees * (M_PI / 180);
    }

    // Convert radians to degrees
    static double radToDeg(double radians) {
        return radians * (180 / M_PI);
    }
} // namespace convert
#endif