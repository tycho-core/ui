//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 6:59:59 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "button.h"
#include "ui/image.h"
#include <functional>

using namespace tycho::engine;

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(TYCHO_UI_ABI, button)	

	button::button(const char* name, graphics::renderer_ptr renderer, graphics::texture_ptr tex) :
		ui::widget(name, bf_selectable)
	{
        using namespace std::placeholders;

		m_textures[texture_selected] = m_textures[texture_unselected] = tex;
		m_image = image_ptr(new image("tmp", renderer, tex));
		bind_highlighted_event(std::bind(&button::handle_highlighted_event, this, _1));
		bind_selected_event(std::bind(&button::handle_selected_event, this, _1));
	}
	
	button::button(const char* name, graphics::renderer_ptr renderer, graphics::texture_ptr unselected, graphics::texture_ptr selected) :
		ui::widget(name, bf_selectable)
	{
        using namespace std::placeholders;

		m_textures[texture_selected] = selected;
		m_textures[texture_unselected] = unselected;
		m_image = image_ptr(new image("tmp", renderer, unselected));
		bind_highlighted_event(std::bind(&button::handle_highlighted_event, this, _1));
		bind_selected_event(std::bind(&button::handle_selected_event, this, _1));
	}
		
	void button::set_texture(texture t, graphics::texture_ptr tp)
	{
		m_textures[t] = tp;
	}
	
	void button::render(render_info& ri)
	{		
		ri.matrix_stack.push_mul(get_transform().get_matrix());
		m_image->render(ri);
		ri.matrix_stack.pop();
	}

	void button::handle_selected_event(const ui::widget::selected_event&)
	{
		raise_onclick_event(onclick_event());
	}
	
	void button::handle_highlighted_event(const ui::widget::highlighted_event& evt)
	{
		m_image->set_texture(m_textures[evt.value ? texture_selected : texture_unselected]);
	}

} // end namespace
} // end namespace
