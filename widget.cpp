//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 6:57:53 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "widget.h"
#include "engine/globals.h"
#include "input/interface.h"

using namespace tycho::engine;

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(TYCHO_UI_ABI, widget)	

	widget::widget(const char* name, int behaviour, const char* input_group_name, input::interface* ii, const input::action* input_actions) : 
		m_ref_count(0),
		m_behaviour(behaviour),
		m_input_group_name(input_group_name),
		m_input_actions(input_actions),
		m_name(name),
        m_ii(ii)
	{
		m_transform = math::srt_transformf::create_identity();
	}
	
	widget::~widget() 
	{}

	widget& widget::set_transform(const math::srt_transformf& transform)
	{
		m_transform = transform;
		return *this;
	}
	
	const math::srt_transformf& widget::get_transform() const
	{
		return m_transform;
	}

	void widget::give_focus()
	{
		m_ii->push_action_group(0, /// \todo set input group correctly
			this->get_input_group_name(),
			this->get_input_actions(), this);
	}

	void widget::remove_focus()
	{
		m_ii->pop_action_group(0, 
			this->get_input_group_name(),
			this->get_input_actions());
	}

	bool widget::supports_behaviour(behaviour_flag f)
	{
		return (m_behaviour & f) > 0;
	}

	widget_ptr widget::find_widget(const char* name)
	{
		// must be the leaf
		if(name)
			return widget_ptr();
		return widget_ptr(this);
	}

	bool widget::check_name(const char* name, const char*& next)
	{
		if(!name) 
			return false;
		
		const size_t len = m_name.length();
		const char* end = &name[len];
		if((core::strncmp(name, m_name.c_str(), static_cast<int>(len)) == 0) &&
		   (*end == '.' || *end == 0))
		{
			// name matches, advance to next part.
			while(*end && *end != '.')
				++end;
			if(*end == '.')
				next = end+1;
			else
				next = 0;
			return true;			
		}
		return false;
	}

} // end namespace
} // end namespace
