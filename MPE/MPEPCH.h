#pragma once

/**
 * @file MPEPCH.h
 * @brief Precompiled header file for the MPE engine.
 */

#ifdef MPE_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#ifdef MPE_PLATFORM_LINUX or MPE_PLATFORM_OSX
#include <unistd.h>
#endif

// BASIC
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include <random>

// STRING, STRING MANIPULATION, FILE MANIPULATION
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

// DATA STRUCTURES
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>