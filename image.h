//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 7:33:18 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __IMAGE_H_F3292C1A_E355_4550_B023_BB61E1AF685D_
#define __IMAGE_H_F3292C1A_E355_4550_B023_BB61E1AF685D_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "graphics/forward_decls.h"
#include "graphics/shader/forward_decls.h"
#include "ui/widget.h"
#include "engine/entity/forward_decls.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	/// displays a 2d image
    class TYCHO_UI_ABI image : public ui::widget
    {
    public:
		/// constructor
		image(const char* name, graphics::renderer_ptr r, graphics::texture_ptr);
		
		/// Set the texture to use on the image.
		void set_texture(graphics::texture_ptr);
		
		/// \name Widget interface
		//@{
		void render(render_info&);
		virtual void update() {}
		//@}
		
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(TYCHO_UI_ABI, image)			
		graphics::texture_ptr	m_texture;
		engine::entity::mesh_ptr		m_mesh;
    };
	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(TYCHO_UI_ABI, image)	

} // end namespace
} // end namespace

#endif // __IMAGE_H_F3292C1A_E355_4550_B023_BB61E1AF685D_
