//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Tuesday, 20 May 2008 4:49:15 PM
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "graphics/texture_utils.h"
#include "graphics/renderer.h"
#include "ui/layout.h"
#include "ui/button.h"
#include "ui/panel.h"
#include "ui/image.h"
#include "ui/label.h"
#include "core/memory.h"
#include "core/memory/allocator.h"
#include "core/flexint.h"
#include "core/console.h"
#include "core/string.h"
#include "math/vector3.h"
#include "io/stream.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cerrno>
#include <cstdlib>

using namespace tycho;

//////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////
namespace tycho
{
namespace ui
{

	namespace detail
	{
	namespace parser
	{
		struct token_def
		{	
			int token;
			char str[128];
		};
		
		// layout file parser 
        enum tokens
        {
		    #include "layout_grammar.h"
        };

		#include "layout_grammar.inl"	
	}
	namespace lexer
	{
        using namespace parser;

		// layout lexer
		#include "core/flex_lexer.h"
		#include "layout_lexer.inl"
	} // end namespace
	} // end namespace
	
	
    TYCHO_UI_ABI bool load_layout(input::interface* input, io::interface* io, graphics::renderer_ptr renderer, io::stream_ptr istr, std::vector<widget_ptr>& widgets)
	{
		void *lemon_state = detail::parser::ParseAlloc(core::malloc);
		detail::parser::state state;
		for(int i = 0; i < detail::parser::MaxDepth; ++i)
			detail::parser::reset_params(state.params[i]);
		state.has_error = false;
		state.renderer  = renderer;
        state.io = io;
        state.ii = input;
		detail::lexer::yyFlexLexer lexer(istr.get(), 0);		
		int token;
		while((token = lexer.yylex()) != 0)
		{
			// ignore whitespace
			detail::parser::token_def def;
			def.token = token;
			core::strncpy(def.str, lexer.YYText(), 128);
			detail::parser::Parse(lemon_state, token, def, &state); 
			if(state.has_error)
			{
				core::console::write("unknown(%d) : Error parsing UI Layout file", lexer.lineno());
				break;
			}
		}	
		if(!state.has_error)
		{
			// push empty token to finish off parsing and cleanup
			detail::parser::Parse(lemon_state, 0, detail::parser::token_def(), &state);
			detail::parser::ParseFree(lemon_state, core::free);
			if(state.has_error)
			{
				core::console::write("unknown(%d) : Error parsing UI Layout file", lexer.lineno());
				return false;
			}
		}			
		TYCHO_ASSERT(state.cur_depth == 0);
		widgets.swap(state.cur_params().pp.widgets);
		return true;
	}

} // end namespace
} // end namespace

