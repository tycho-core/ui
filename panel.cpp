//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 7:00:49 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "panel.h"
#include <algorithm>


//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{
	TYCHO_INTRUSIVE_PTR_FUNC_IMPL(TYCHO_UI_ABI, panel)

	namespace detail
	{
		enum panel_input_actions
		{
			panel_highlight_next, 
			panel_highlight_prev, 
			panel_select
		};
		
		static input::action panel_actions[] = {
			{ "ui.panel.highlight_next",  detail::panel_highlight_next,	input::event_type_key },
			{ "ui.panel.highlight_prev",  detail::panel_highlight_prev,	input::event_type_key },
			{ "ui.panel.select",  detail::panel_select,	input::event_type_key },
			{ 0, 0 }
		};	
	}
	
	panel::panel(input::interface * ii, const char* name) :
		widget(name, bf_default, "ui.panel", ii, detail::panel_actions),
		m_selected_widget(0)
	{}

	void panel::add_widget(widget_ptr w)
	{
		m_widgets.push_back(w);
	}
	
	void panel::remove_widget(widget_ptr w)
	{
		widgets::iterator it = std::find(m_widgets.begin(), m_widgets.end(), w);
		if(it != m_widgets.end())
		{
			if(m_cur_highlighted_widget == w)
			{
				highlight_next_widget(1);
				if(m_cur_highlighted_widget == w)
					m_cur_highlighted_widget = widget_ptr();
			}
			m_widgets.erase(it);
		}
	}

	/// highlight the i'th widget
	void panel::highlight_widget(int i)
	{
		TYCHO_ASSERT(i < (int)m_widgets.size());
		if(m_cur_highlighted_widget)
			m_cur_highlighted_widget->raise_highlighted_event(highlighted_event(false));
		m_widgets[i]->raise_highlighted_event(highlighted_event(true));
		m_cur_highlighted_widget = m_widgets[i];
		m_selected_widget = i;
	}

	void panel::highlight_next_widget(int dir)
	{
		if(m_widgets.size() == 0)
			return;	
		widget_ptr& from = m_cur_highlighted_widget;
		widget_ptr to;
		int num_widgets = (int)m_widgets.size();
		for(int i = 1; i < num_widgets-1; ++i)
		{
			int next = (m_selected_widget + i * dir + num_widgets) % num_widgets;
			if(m_widgets[next]->supports_behaviour(widget::bf_selectable))
			{
				m_selected_widget = next;
				to = m_widgets[next];
				break;
			}
		}		
		m_cur_highlighted_widget = travel(from, to);
	}
	
	void panel::select_widget()
	{
		widget_ptr& w = m_widgets[m_selected_widget];
		TYCHO_ASSERT(w);
		w->raise_selected_event(selected_event(true));
	}
	
	widget_ptr panel::travel(widget_ptr from, widget_ptr to)
	{
		if(from == to)
			return from;
			
		// inform the first widget its about to lose focus
		if(to && from)
			from->raise_highlighted_event(highlighted_event(false));
		
		// give the the second widget focus
		if(to)
		{
			to->raise_highlighted_event(highlighted_event(true));
			return to;
		}
		return from;
	}
	
	void panel::render(render_info& ri)
	{
		ri.matrix_stack.push_mul(get_transform().get_matrix());
		widgets::iterator it = m_widgets.begin();
		widgets::iterator end = m_widgets.end();
		while(it != end)
		{
			(*it)->render(ri);
			++it;
		}		
		ri.matrix_stack.pop();
	}

	const input::action* panel::get_input_actions() const
	{
		return detail::panel_actions;
	}
	
	bool panel::handle_key(int action_id, input::key_type /*key*/, input::key_state /*state*/)
	{
		switch(action_id)
		{
			case detail::panel_highlight_next : highlight_next_widget(1); return true;
			case detail::panel_highlight_prev : highlight_next_widget(-1); return true;
			case detail::panel_select : select_widget(); return true;
		}
		return false;
	}	

	widget_ptr panel::find_widget(const char* name)
	{
		// check to see if our name matches
		const char* next;				
		for(size_t i = 0; i < m_widgets.size(); ++i)
		{
			widget_ptr w = m_widgets[i];
			if(w->check_name(name, next))
			{
				return w->find_widget(next);
			}
		}
		return widget_ptr();
	}
	
} // end namespace
} // end namespace
