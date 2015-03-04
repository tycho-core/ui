//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 6 May 2008 7:47:55 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __EVENT_H_AF184AB1_5B02_485D_B97B_279089A7CC7D_
#define __EVENT_H_AF184AB1_5B02_485D_B97B_279089A7CC7D_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include <functional>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// MACROS
//////////////////////////////////////////////////////////////////////////////

// helper macros to simplify defining events.	

#define TYCHO_UI_EVENT(_name) \
		void raise_##_name##_event(_name##_event evt) { raise_event(m_##_name##_event_cbs, evt); } \
		void bind_##_name##_event(_name##_event::cb_type cb) { m_##_name##_event_cbs.push_back(cb); } \
		_name##_event::cb_list m_##_name##_event_cbs;
    	
#define TYCHO_UI_SIMPLE_EVENT(_name) \
		struct _name##_event : ui::event_base<_name##_event> {}; \
		TYCHO_UI_EVENT(_name)
				
#define TYCHO_UI_BOOL_EVENT(_name) \
		struct _name##_event : ui::event_base<_name##_event> { _name##_event(bool v) : value(v) {} bool value; }; \
		TYCHO_UI_EVENT(_name)

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	/// base class for all events
    class TYCHO_UI_ABI event
    {
    public:
		virtual ~event() {}
		virtual const char* name() { return "ui::event"; }
		
    private:
		// sender		    
    };
    
    /// inherit from this passing your class type as the template 
    /// parameter (CRTP) instead of from an event directly so you
    /// get all the necessary type definitions
	template<class T>
	class TYCHO_UI_ABI event_base : public event
	{
	public:
		typedef std::function<void(const T&)>  cb_type;
		typedef std::vector<cb_type> cb_list;		
	};    

} // end namespace
} // end namespace

#endif // __EVENT_H_AF184AB1_5B02_485D_B97B_279089A7CC7D_
