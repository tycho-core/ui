//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 20 May 2008 1:11:46 AM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "label.h"
#include "engine/entity/mesh.h"
#include "graphics/shapes.h"
#include "graphics/vertex_formats.h"
#include "graphics/vertex_buffer.h"
#include "graphics/index_buffer.h"
#include "graphics/texture_base.h"
#include "graphics/camera.h"
#include "core/debug/assert.h"
#include "core/string.h"

using namespace tycho::engine;

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(TYCHO_UI_ABI, label)	

	label::label(const char* name, graphics::renderer_ptr renderer, graphics::text::font_ptr f, int font_size, int max_len) :
		widget(name),
		m_font(f),
		m_font_size(font_size),
        m_renderer(renderer),
		m_mesh(new entity::mesh(renderer, "label_mesh")),
        m_handle(0)
	{
	}
	
	label::~label()
	{
		if(m_handle)
		{
			m_renderer->get_font_manager().release(m_handle);
			m_handle = 0;
		}	
	}
	
	/// set the font to use
	void label::set_font(graphics::text::font_ptr f, int size)
	{
		m_font = f;
		m_font_size = size;
	}
	
	/// set the text to render
	void label::set_text(const char* str)
	{
		m_text = str;
		m_dirty = true;
	}
	
	void label::render(render_info& ri)
	{
		if(m_dirty)
		{
			if(m_handle)
			{
				m_renderer->get_font_manager().release(m_handle);
				m_handle = 0;
			}
				
			m_handle = m_renderer->get_font_manager().build_string(m_font, m_font_size, m_text.c_str(), m_text.length());
			graphics::texture_base_ptr tex = m_renderer->get_font_manager().get_texture(m_handle);
			
			// generate correct size to get 1-1 pixel mapping, this is dependent on the render target size
			const math::rectf& uvs = m_renderer->get_font_manager().get_uvs(m_handle);
			const math::vector2i& size = m_renderer->get_font_manager().get_size(m_handle); // in pixels
			float rt_width = (float)ri.camera->get_render_target()->get_width();
			float rt_height = (float)ri.camera->get_render_target()->get_height();
			float width = size.x() / rt_width;
			float height = size.y() / rt_height;			
			math::srt_transformf srt = get_transform();
			srt.set_scale(math::vector3f(width, height, 1));
			srt.set_translation(srt.get_translation() + math::vector3f(width/2, height/2,0));
			set_transform(srt);			
			math::matrix4x4f mat(math::matrix4x4f::create_identity());
			float half_texel = 1.0f / (2.0f * rt_width);
			mat.set_translation(math::vector3f(-half_texel, -half_texel, 0));
			m_mesh->set_mesh(graphics::create_plane(m_renderer, math::vector2f(1, 1), 
							 graphics::shape_create_normals | graphics::shape_create_uvs, mat, uvs));			
			m_mesh->set_shader(m_renderer->create_system_shader(graphics::system_shader_ui_string)).set("diffuse_texture", tex.get());
			m_dirty = false;
		}
				
		m_mesh->set_world_mat(get_transform().get_matrix() * ri.matrix_stack.head());
		m_mesh->render(ri.renderer, ri.camera);
	}

} // end namespace
} // end namespace

