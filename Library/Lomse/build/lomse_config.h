//---------------------------------------------------------------------------------------
// This file is part of the Lomse library.
// Lomse is copyrighted work (c) 2010-2016. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this 
//      list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright notice, this
//      list of conditions and the following disclaimer in the documentation and/or
//      other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// For any comment, suggestion or feature request, please contact the manager of
// the project at cecilios@users.sourceforge.net
//---------------------------------------------------------------------------------------

#ifndef __LOMSE_CONFIG_H__
#define __LOMSE_CONFIG_H__

//==================================================================
// Template configuration file.
// Variables are replaced by CMake settings
//==================================================================

//---------------------------------------------------------------------------------------
// paths, for test scores and for fonts
//---------------------------------------------------------------------------------------
#define TESTLIB_SCORES_PATH         "/usr/local/share/lomse/test-scores/"
#define TESTLIB_FONTS_PATH          "/usr/local/share/lomse/fonts/"
#define LOMSE_FONTS_PATH            "/usr/local/share/lomse/fonts/"


//---------------------------------------------------------------------------------------
// platform and compiler
//---------------------------------------------------------------------------------------
#ifdef _WIN32
#define LOMSE_PLATFORM_WIN32      1
#define LOMSE_PLATFORM_UNIX       0
#else
#define LOMSE_PLATFORM_WIN32      0
#define LOMSE_PLATFORM_UNIX       1
#endif

#ifdef _MSC_VER
#define LOMSE_COMPILER_MSVC       1
#else
#define LOMSE_COMPILER_MSVC       0
#endif


//---------------------------------------------------------------------------------------
// what are you doing?
//    - creating the library as shared library   LOMSE_CREATE_DLL == 1
//    - using the library as shared library      LOMSE_USE_DLL == 1
//    - creating the library as static library   LOMSE_CREATE_DLL == 0 
//    - using the library as static library      LOMSE_USE_DLL == 0
//---------------------------------------------------------------------------------------
#define LOMSE_CREATE_DLL    0
#define LOMSE_USE_DLL       0

//---------------------------------------------------------------------------------------
// build options
//---------------------------------------------------------------------------------------
#define ON 1
#define OFF 0

// Debug build: include debug options
#define LOMSE_DEBUG                 OFF 

// Accept without warning/error LDP v1.5 syntax
#define LOMSE_COMPATIBILITY_LDP_1_5     ON

// Enable debug logs. It is independent of build mode: debug or release
#define LOMSE_ENABLE_DEBUG_LOGS     OFF

// Enable compressed formats (requires zlib)
#define LOMSE_ENABLE_COMPRESSION    OFF

// Enable png format (requires pnglib and zlib)
#define LOMSE_ENABLE_PNG    OFF

#endif  // __LOMSE_CONFIG_H__

