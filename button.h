//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 6:59:59 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __BUTTON_H_B55B52A7_07A3_4F7A_949F_EAF8D0C6FF53_
#define __BUTTON_H_B55B52A7_07A3_4F7A_949F_EAF8D0C6FF53_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/forward_decls.h"
#include "ui/widget.h"
#include "ui/forward_decls.h"

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

    class TYCHO_UI_ABI button : public ui::widget
    {
    public:
		enum texture
		{
			texture_unselected,
			texture_selected,
			texture_count
		};
				
    public:
		/// construct with a single texture, it is used for both selected and unselected states
		button(const char* name, graphics::renderer_ptr renderer, graphics::texture_ptr);
		
		/// construct with different textures for selected and unselected
		button(const char* name, graphics::renderer_ptr renderer, graphics::texture_ptr unselected, graphics::texture_ptr selected);
		
		/// set a texture
		void set_texture(texture t, graphics::texture_ptr);
		
		/// \name ui::widget interface
		//@{
		virtual void render(render_info&);		
		//@}
		
		TYCHO_UI_SIMPLE_EVENT(onclick)
		
	private:
		/// \name event handlers
		//@{
		void handle_selected_event(const ui::widget::selected_event& evt);
		void handle_highlighted_event(const ui::widget::highlighted_event& evt);
		//@}
    
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(TYCHO_UI_ABI, button)			
		graphics::texture_ptr m_textures[texture_count];
		ui::image_ptr m_image;
    };
	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(TYCHO_UI_ABI, button)	

} // end namespace
} // end namespace

#endif // __BUTTON_H_B55B52A7_07A3_4F7A_949F_EAF8D0C6FF53_
