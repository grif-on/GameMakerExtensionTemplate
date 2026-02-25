/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2017 Chukong Technologies
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

https://axmol.dev/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/



//!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\ 

// NOTE
// This platform config taken from Axmol game engine almost as is.
// The only things that i changed is:
// replaced AX_ prefix with GM_ one
// and *DISABLED* error message if platform is GM_PLATFORM_UNKNOWN.
//
// That being said, updating/maintaining of this file should be as easy
// as downloading it from Axmol's github and re-applying above changes.

//!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\   //!\\ 



#pragma once
/// @cond DO_NOT_SHOW

#if __has_include(<winapifamily.h>)
#    include <winapifamily.h>
#endif

/**
  Config of cocos2d-x project, per target platform.

  THIS FILE MUST NOT INCLUDE ANY OTHER FILE
*/

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which CC uses.
#define GM_PLATFORM_UNKNOWN 0
#define GM_PLATFORM_WIN32   1
#define GM_PLATFORM_WINUWP  2
#define GM_PLATFORM_LINUX   3
#define GM_PLATFORM_OSX     4
#define GM_PLATFORM_ANDROID 5
#define GM_PLATFORM_IOS     6
#define GM_PLATFORM_TVOS    7
#define GM_PLATFORM_WASM    8

// alias platform macros
#define GM_PLATFORM_WINRT      GM_PLATFORM_WINUWP
#define GM_PLATFORM_MAC        GM_PLATFORM_OSX
#define GM_PLATFORM_EMSCRIPTEN GM_PLATFORM_WASM

// Determine target platform by compile environment macro.
#define GM_TARGET_PLATFORM GM_PLATFORM_UNKNOWN

// Apple: Mac and iOS
#if defined(__APPLE__) && !defined(__ANDROID__)  // exclude android for binding generator.
#    include <TargetConditionals.h>
#    if TARGET_OS_IPHONE  // TARGET_OS_IPHONE includes TARGET_OS_IOS TARGET_OS_TV and TARGET_OS_WATCH. see
                          // TargetConditionals.h
#        undef GM_TARGET_PLATFORM
#        define GM_TARGET_PLATFORM GM_PLATFORM_IOS
#        if TARGET_OS_TV && !defined(GM_TARGET_OS_TVOS)
#            define GM_TARGET_OS_TVOS 1
#        endif
#    elif TARGET_OS_MAC
#        undef GM_TARGET_PLATFORM
#        define GM_TARGET_PLATFORM GM_PLATFORM_MAC
#    endif
#endif

// win32
#if defined(_WIN32) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
#    undef GM_TARGET_PLATFORM
#    define GM_TARGET_PLATFORM GM_PLATFORM_WIN32
#endif

// WinRT (Windows 10.0 UWP App)
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_APP)
// Windows Store or Universal Windows Platform
#    undef GM_TARGET_PLATFORM
#    define GM_TARGET_PLATFORM GM_PLATFORM_WINRT
#endif

// linux
#if defined(__linux__)
#    undef GM_TARGET_PLATFORM
#    define GM_TARGET_PLATFORM GM_PLATFORM_LINUX
#endif

#if defined(__EMSCRIPTEN__)
#    undef GM_TARGET_PLATFORM
#    define GM_TARGET_PLATFORM GM_PLATFORM_WASM
#endif

// android, override linux
#if defined(__ANDROID__) || defined(ANDROID)
#    undef GM_TARGET_PLATFORM
#    define GM_TARGET_PLATFORM GM_PLATFORM_ANDROID
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// *DISABLED* // // check user set platform
// *DISABLED* // #if !GM_TARGET_PLATFORM
// *DISABLED* // #    error "Cannot recognize the target platform; are you targeting an unsupported platform?"
// *DISABLED* // #endif

#if (GM_TARGET_PLATFORM == GM_PLATFORM_WIN32)
#    ifndef __MINGW32__
#        pragma warning(disable : 4127)
#    endif
#endif  // GM_PLATFORM_WIN32

/*
The google/angle is library which translate native graphics API to GLES3+ APIs
repo: https://github.com/google/angle
windows: d3d9/d3d11/Desktop GL/Vulkan
macOS/iOS: Metal
Android: GLES/Vulkan
Linux: Desktop GL/Vulkan
*/
// 0: indicate: not use GLES
// mac/iOS/android use system builtin GL/GLES, not ANGLE
// Windows: use ANGLE GLES
#ifndef GM_GLES_PROFILE
#    if defined(__ANDROID__)
#        define GM_GLES_PROFILE 200
#    elif (GM_TARGET_PLATFORM == GM_PLATFORM_WINRT)
#        define GM_GLES_PROFILE 300
#    else
#        define GM_GLES_PROFILE 0
#    endif
#endif

#define GM_GLES_PROFILE_DEN 100

#if ((GM_TARGET_PLATFORM == GM_PLATFORM_ANDROID) || (GM_TARGET_PLATFORM == GM_PLATFORM_IOS) || \
     (GM_TARGET_PLATFORM == GM_PLATFORM_WINRT) || (GM_TARGET_PLATFORM == GM_PLATFORM_WASM))
#    define GM_PLATFORM_MOBILE
#else
#    define GM_PLATFORM_PC
#endif

#if defined(__APPLE__)
#    if !defined(GM_USE_GL)
#        define GM_USE_METAL 1
#    endif
#else  // win32,linux,winuwp,android
#    if !defined(GM_USE_GL)
#        define GM_USE_GL 1
#    endif
#endif

// ## SIMD detections
#if !defined(GM_NEON_INTRINSICS)
#    if (GM_TARGET_PLATFORM != GM_PLATFORM_WASM)
#        if defined(__arm64__) || defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM) || defined(__ARM_NEON__)
#            define GM_NEON_INTRINSICS 1
#        endif
#    endif
#endif

#ifdef GM_SSE_INTRINSICS
// axmol math ISA require SSE2 at latest
#    if defined(__SSE4_1__)
#        include <smmintrin.h>
#    else
#        include <emmintrin.h>
#    endif
typedef __m128 _xm128_t;
#elif defined(GM_NEON_INTRINSICS)
#    include <arm_neon.h>
typedef float32x4_t _xm128_t;
#endif

/// @endcond