//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Monday, 5 May 2008 6:57:53 PM
//////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER

#ifndef __WIDGET_H_CB417037_4478_4450_8E81_C363D7C4A62C_
#define __WIDGET_H_CB417037_4478_4450_8E81_C363D7C4A62C_

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "ui/ui_abi.h"
#include "ui/forward_decls.h"
#include "ui/event.h"
#include "graphics/forward_decls.h"
#include "input/types.h"
#include "input/forward_decls.h"
#include "math/matrix4x4.h"
#include "math/srt_transform.h"
#include "math/matrix_stack.h"
#include "core/colour/rgba.h"
#include "core/debug/assert.h"
#include <string>

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////

namespace tycho
{
namespace ui
{

	/// A widget is the base class of all visual elements in the ui system. It provides
	/// an interface so base classes can do widgety things like draw, handle mouse clicks/controllers, 
	/// accept input etc. All widgets are full 3d objects so can be positioned, orientated and
	/// animated within the world. The UI uses coordinates in clip space so they are 
	/// camera view independent with a Z of 0.0 being the near clip place and 1 being the far
	/// clip plane. Basically if you want the widget to align with the screen like a classic 
	/// 2d widget then just set it's Z to 0.0.
    class TYCHO_UI_ABI widget : 
		public input::input_handler
    {
    public:
		struct render_info
		{
			graphics::renderer_ptr	renderer;
			graphics::camera_ptr	camera;
			core::rgba				tint; ///< multiplied into diffuse to tint the widget, use (1,1,1,a) where 
			                              ///< a is in [0, 1] to fade the widget.	
			math::matrix_stack<float> matrix_stack;			                              		
		};
		
		enum behaviour_flag
		{
			bf_invalid,
			bf_none       = (1 << 0),
			bf_selectable = (1 << 1),
			bf_default    = bf_none					
		};
		
    public:
		widget(const char* name, int behaviour = bf_default,
			   const char* input_group_name = 0, 
			   input::interface* ii = 0, const input::action* input_actions = 0);
		virtual ~widget();
		
		/// \name
		//@{ interface
		virtual void render(render_info&) = 0;		
		virtual void give_focus();
		virtual void remove_focus();
		
    	/// Find a widget of the passed name. This name is in format panel01.panel02.button
    	/// and each derived class checks to see if its name matches and if is not the leaf
    	/// removes its name and passes it on down the list. The default implementation 
    	/// compares with this widgets name so on container widgets need implement this.
    	virtual widget_ptr find_widget(const char* name);		
		//@}
		
		/// \retursn the name of the widget
		const char* get_name() const { return m_name.c_str(); }
		
		/// \returns the name of this widgets input group
		const char* get_input_group_name() const { return m_input_group_name; }		
		
		/// \returns the actions this widget exposes
        virtual const input::action* get_input_actions() const { return m_input_actions; }
		
		/// set the transformation to use when rendering this component
    	widget& set_transform(const math::srt_transformf& transform);
    	
    	/// \returns the transform for the widget
    	const math::srt_transformf& get_transform() const;				
    	
    	/// \returns true if the widget support the specified behaviour
    	bool supports_behaviour(behaviour_flag);
    					
		/// Checks the name of the object matches this widget. 
		/// \returns true if the name is correct and sets the next pointer to the start 
		///          of the next part of the name or 0 if at the end.
		bool check_name(const char* name, const char*& next);
    					
		template<class dst_type>
		boost::intrusive_ptr<dst_type> find_widget_t(const char *name)
		{
			return boost::static_pointer_cast<dst_type>(find_widget(name));
		}
		    					
		/// \name Events
		//@{				
		TYCHO_UI_BOOL_EVENT(selected)		
		TYCHO_UI_BOOL_EVENT(highlighted)			
		//@}
		
	protected:		
    	template<class T, class S>
    	void raise_event(T& cbs, const S &s)
    	{
    		typename T::iterator it = cbs.begin();
    		typename T::iterator end = cbs.end();
    		for(; it != end; ++it)
    			(*it)(s);
    	}
				
    private:
		TYCHO_INTRUSIVE_PTR_FRIEND_DECLS(TYCHO_UI_ABI, widget)			
    	
		math::srt_transformf m_transform;
		int m_ref_count;
		int m_behaviour;
		const char* m_input_group_name;
		const input::action* m_input_actions;
		std::string m_name;
        input::interface* m_ii;

	protected:
		void add_ref() { ++m_ref_count; }
		void dec_ref() { --m_ref_count; if(m_ref_count == 0) delete this;	}
    };
    
	TYCHO_INTRUSIVE_PTR_FUNC_DECLS(TYCHO_UI_ABI,  widget)	
	
} // end namespace
} // end namespace

#endif // __WIDGET_H_CB417037_4478_4450_8E81_C363D7C4A62C_
