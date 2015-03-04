//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 20 May 2008 5:35:26 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __WINDOW_MANAGER_H_CD8AEFA8_8B48_4042_B989_D85DE544DBEE_
#define __WINDOW_MANAGER_H_CD8AEFA8_8B48_4042_B989_D85DE544DBEE_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "ui/widget.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{
	
	/// a window manager controls layout and is responsible for tracking
	/// input focus.
    class TYCHO_UI_ABI window_manager
    {
    public:
		void add_widget(widget_ptr);
		void remove_widget(widget_ptr);
		
    private:
		typedef std::list<ui::widget_ptr> widget_list;
		widget_list m_widgets;
		widget_ptr  m_focus_widget;
    };

} // end namespace
} // end namespace

#endif // __WINDOW_MANAGER_H_CD8AEFA8_8B48_4042_B989_D85DE544DBEE_
