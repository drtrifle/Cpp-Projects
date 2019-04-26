#pragma once

#ifdef HZ_PLATFORM_WINDOWS

    //Shortcut instead of typing __declspec import/export
    #ifdef HZ_BUILD_DLL
        #define HAZEL_API __declspec(dllexport)
    #else
        #define HAZEL_API __declspec(dllimport)
    #endif
#else
    #error  Hazel only Supports Windows!

#endif

#define BIT(x) (1 << x)