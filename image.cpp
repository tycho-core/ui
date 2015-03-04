//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 7:33:19 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/image.h"
#include "graphics/shapes.h"
#include "graphics/renderer.h"
#include "graphics/camera.h"
#include "graphics/texture.h"
#include "graphics/shader/parameter_buffer_view.h"
#include "engine/entity/mesh.h"

using namespace tycho::engine;

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{	
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(TYCHO_UI_ABI, image)

	image::image(const char* name, graphics::renderer_ptr r, graphics::texture_ptr tex) :
		widget(name),
		m_texture(tex),
		m_mesh(new entity::mesh(r, "image_mesh"))
	{
		m_mesh->set_mesh(graphics::create_plane(r, math::vector2f(1, 1), graphics::shape_create_normals | graphics::shape_create_uvs));			
		m_mesh->set_shader(r->create_system_shader(graphics::system_shader_ui)).set("diffuse_texture", tex.get());
	}
	
	void image::set_texture(graphics::texture_ptr tex)
	{
		m_texture = tex;
		m_mesh->get_shader_param_view().set("diffuse_texture", tex.get());		
	}
	
	void image::render(render_info& ri)
	{	
		m_mesh->set_world_mat(get_transform().get_matrix() * ri.matrix_stack.head());
		m_mesh->render(ri.renderer, ri.camera);
	}

} // end namespace
} // end namespace

