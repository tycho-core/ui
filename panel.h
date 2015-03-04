//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 7:00:49 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __PANEL_H_2961AA10_6D03_45A4_B343_546FF5976C8C_
#define __PANEL_H_2961AA10_6D03_45A4_B343_546FF5976C8C_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "ui/widget.h"
#include "input/types.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	/// A panel can contain multiple widgets, and as it is a widget itself can have 
	/// sub panels. These just give a convenient grouping of widgets that can be 
	/// positioned and orientated as a unit.
    class TYCHO_UI_ABI panel : 
		public ui::widget
    {
    public:
		/// constructor
        panel(input::interface * ii, const char* name);		
		
		/// add a widget to the panel
		void add_widget(widget_ptr);
		
		/// remove a widget from the panel
		void remove_widget(widget_ptr);

		/// highlight the i'th widget
		void highlight_widget(int i);
								
		/// select the current widget
		void select_widget();
		
		/// \name ui::widget interface
		//@{
		virtual const input::action* get_input_actions() const;
		virtual void render(render_info&);
		virtual void update() {}
    	virtual widget_ptr find_widget(const char* name);		
		//@}
		
		/// \name input::handler interface
		//@{
		virtual bool handle_key(int /*action_id*/, input::key_type /*key*/, input::key_state /*state*/);
		//@}

	private:
		widget_ptr travel(widget_ptr from, widget_ptr to);

		/// highlight the next widget in the tab order, +1 == next, -1 == prev.
		void highlight_next_widget(int dir);
				
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(TYCHO_UI_ABI, panel)			

		typedef std::vector<widget_ptr> widgets;	
		widgets m_widgets;
		widget_ptr m_cur_highlighted_widget;
		int		m_selected_widget;
    };
	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(TYCHO_UI_ABI, panel)	

} // end namespace
} // end namespace


#endif // __PANEL_H_2961AA10_6D03_45A4_B343_546FF5976C8C_
