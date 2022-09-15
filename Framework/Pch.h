#ifndef _PCH_H_
#define _PCH_H_

#define abstract_class class

#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib, "libMinHook.x64.MDd.lib")		// Arch: x64 RTL: MDd
#else
#pragma comment(lib, "libMinHook.x64.MD.lib")		// Arch: x64 RTL: MD
#endif
#else
#ifdef _DEBUG
#pragma comment(lib, "libMinHook.x86.MDd.lib")		// Arch: x86 RTL: MDd
#else
#pragma comment(lib, "libMinHook.x86.MD.lib")		// Arch: x86 RTL: MD
#endif
#endif

#include <iostream>
#include <cstdlib>
#include <functional>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <cstdint>
#include <string>
#include <locale>
#include <codecvt>
#include <unordered_map>

#include "MinHook.h"

#include "Singleton.hpp"
#include "Event.hpp"
#include "Logger.h"

#endif // _PCH_H_

