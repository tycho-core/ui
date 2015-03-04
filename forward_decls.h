//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 9:00:07 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __FORWARD_DECLS_H_914041FF_90F8_400C_A607_EC3D1A86E9AC_
#define __FORWARD_DECLS_H_914041FF_90F8_400C_A607_EC3D1A86E9AC_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "core/intrusive_ptr.h"
#include "core/shared_ptr.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	TYCHO_DECLARE_SHARED_PTR(TYCHO_UI_ABI, font)
	TYCHO_DECLARE_SHARED_PTR(TYCHO_UI_ABI, mono_font)
	
	TYCHO_DECLARE_INTRUSIVE_PTR(TYCHO_UI_ABI, widget)
	TYCHO_DECLARE_INTRUSIVE_PTR(TYCHO_UI_ABI, image)
	TYCHO_DECLARE_INTRUSIVE_PTR(TYCHO_UI_ABI, panel)
	TYCHO_DECLARE_INTRUSIVE_PTR(TYCHO_UI_ABI, button)
	TYCHO_DECLARE_INTRUSIVE_PTR(TYCHO_UI_ABI, label)

} // end namespace
} // end namespace



#endif // __FORWARD_DECLS_H_914041FF_90F8_400C_A607_EC3D1A86E9AC_
