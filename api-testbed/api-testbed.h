// api-testbed.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <windows.h>

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

extern "C"
{
	#include "extApi.h"
	#include "extApiPlatform.h"
}
