//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 20 May 2008 1:11:46 AM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __LABEL_H_4051BEE3_D8B4_4E9A_9116_272D6CC63FE5_
#define __LABEL_H_4051BEE3_D8B4_4E9A_9116_272D6CC63FE5_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "ui/widget.h"
#include "graphics/forward_decls.h"
#include "graphics/text/forward_decls.h"
#include "graphics/text/font_manager.h"
#include "engine/entity/forward_decls.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	/// Non editable text display
    class TYCHO_UI_ABI label : public widget
    {
    public:
		/// constructor
		label(const char* name, graphics::renderer_ptr, graphics::text::font_ptr, int font_size, int max_len);
		
		/// destructor
		~label();
		
		/// set the font to use
		void set_font(graphics::text::font_ptr, int size);
		
		/// set the text to render
		void set_text(const char*);
		
		/// \name ui::widget interface
		//@{
		virtual void render(render_info&);		
		//@}    
		
	private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(TYCHO_UI_ABI, label)			
		graphics::text::font_ptr m_font;
		int			m_font_size; // in pixels
		std::string m_text;
		graphics::renderer_ptr m_renderer;
		graphics::texture_ptr  m_texture;
		engine::entity::mesh_ptr	   m_mesh;
		graphics::text::font_manager::string_handle m_handle;
		bool m_dirty;
    };
	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(TYCHO_UI_ABI, label)	

} // end namespace
} // end namespace

#endif // __LABEL_H_4051BEE3_D8B4_4E9A_9116_272D6CC63FE5_
