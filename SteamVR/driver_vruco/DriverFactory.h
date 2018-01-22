#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <openvr_driver.h>
#define HMD_DLL_EXPORT extern "C" __declspec(dllexport) 
using namespace vr;

#include "ServerDriver.h"
#include "WatchdogDriver.h"

static ServerDriver server_driver;
static WatchdogDriver watchdog_driver;

HMD_DLL_EXPORT void* HmdDriverFactory(const char* pInterfaceName, int* pReturnCode);