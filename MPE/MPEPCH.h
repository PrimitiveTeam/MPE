#pragma once

/**
 * @file MPEPCH.h
 * @brief Precompiled header file for the MPE engine.
 */

#ifdef MPE_PLATFORM_WINDOWS
#    include <Windows.h>
#endif

#ifdef MPE_PLATFORM_LINUX or MPE_PLATFORM_OSX
#    include <unistd.h>
#endif

// BASIC
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include <utility>

// STRING, STRING MANIPULATION, FILE MANIPULATION
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

// DATA STRUCTURES
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <vector>