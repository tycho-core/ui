//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2013 Martin Slater
// Created : Saturday, 09 November 2013 03:17:15 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef _TEMPLATE_ABI_H_AB8DEB32_8660_45D1_9AE0_0C19C7FB7088
#define _TEMPLATE_ABI_H_AB8DEB32_8660_45D1_9AE0_0C19C7FB7088

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "core/core_abi.h"

#if TYCHO_PC

// DLL interface
#ifdef TYCHO_UI_EXPORTS
#define TYCHO_UI_ABI __declspec(dllexport)
#else
#define TYCHO_UI_ABI __declspec(dllimport)
#endif 

// disable a few warnings globally. should move these into specific cpp's to avoid polluting
// user header files
#pragma warning(disable : 4251) // class needs to have dll-interface to be used by clients of class ''
#pragma warning(disable : 4355) // 'this' : used in base member initializer list

#else // TYCHO_PC

#define TYCHO_UI_ABI

#endif // TYCHO_GC

#ifdef __cplusplus
#include "core/memory/new.h"
#include "core/memory.h"
#include "core/debug/assert.h"
#endif 

#endif // _TEMPLATE_ABI_H_AB8DEB32_8660_45D1_9AE0_0C19C7FB7088
