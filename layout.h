//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Saturday, 24 May 2008 5:39:55 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __LAYOUT_H_345FF729_1ECA_462C_80F5_C3F26E71AB99_
#define __LAYOUT_H_345FF729_1ECA_462C_80F5_C3F26E71AB99_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "ui/forward_decls.h"
#include "graphics/forward_decls.h"
#include "io/forward_decls.h"
#include "input/forward_decls.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	TYCHO_UI_ABI bool load_layout(input::interface*, io::interface* io, graphics::renderer_ptr renderer, io::stream_ptr istr, std::vector<widget_ptr>& widgets);

} // end namespace   
} // end namespace

#endif // __LAYOUT_H_345FF729_1ECA_462C_80F5_C3F26E71AB99_
