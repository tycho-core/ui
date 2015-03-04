//////////////////////////////////////////////////////////////////////////////
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 21 May 2008 11:27:38 PM
//  
// Grammar for ui layout file, built using lemon parser generator.
//////////////////////////////////////////////////////////////////////////////
%token_type		{token_def}
%extra_argument { state * s }
%token_prefix	TY_

%type vec3 { vec3 }
%type float { float }
%type bool { bool }
%type int { int }
%type vec3arg { float }

contents ::= version decls.
version ::= VERSION EQ int SEMI.

// widgets
widget ::= button_widget.
widget ::= image_widget.
widget ::= label_widget.
widget ::= panel_widget.

// widget decls
decl  ::= widget SEMI.
decls ::= decls decl.
decls ::= decl.

// types
vec3arg(A)	::= float(B).   { A = B; }
vec3arg(A)	::= int(B).		{ A = (float)B; }
vec3(A)     ::= LBRACK vec3arg(B) COMMA vec3arg(C) COMMA vec3arg(D) RBRACK. { A.x = B; A.y = C; A.z = D; }
string(A)   ::= STRING(B).	{ A = B; }
int(A)      ::= INT(B).		{ A = atoi(B.str); }
float(A)    ::= FLOAT(B).	{ A = atof(B.str); }
bool(A)     ::= TRUE.		{ A = true; }
bool(A)     ::= FALSE.		{ A = false; }
name(A)     ::= ID(B).		{ A = B; }
name_opt(A) ::= .			{ A.str[0] = 0; }
name_opt(A) ::= name(B).	{ A = B; }

// parameters common to all widgets
common_param ::= TRANS EQ vec3(B) SEMI.		{ s->cur_params().cp.trans = B; }
common_param ::= SCALE EQ vec3(B) SEMI.		{ s->cur_params().cp.scale = B; }
common_param ::= VISIBLE EQ bool(B) SEMI.	{ s->cur_params().cp.visible = B; }

// button widget
button_param  ::= common_param.
button_param  ::= IMAGE EQ string(A) SEMI.				{ core::strncpy(s->cur_params().bp.image, A.str, MAX_STRING); }
button_param  ::= IMAGE_H EQ string(A) SEMI.			{ core::strncpy(s->cur_params().bp.image_h, A.str, MAX_STRING); }
button_params ::= button_param.
button_params ::= button_params button_param.
button_widget_a ::= WIDGET BUTTON. { push_params(s); }
button_widget ::= button_widget_a name_opt(A) LBRACE button_params RBRACE. { create_button_widget(A.str, s); }

// image widget
image_param  ::= common_param.
image_param  ::= IMAGE EQ string(C) SEMI.				{ core::strncpy(s->cur_params().ip.image, C.str, MAX_STRING); }
image_params ::= image_param.
image_params ::= image_params image_param.
image_widget_a ::= WIDGET IMAGE. { push_params(s); }
image_widget ::= image_widget_a name_opt(A) LBRACE image_params RBRACE. { create_image_widget(A.str, s); }

// label widget
label_param  ::= common_param.
label_param  ::= FONT EQ string(A) SEMI.				{ core::strncpy(s->cur_params().lp.font, A.str, MAX_STRING); }
label_param  ::= FONT_SIZE EQ int(A) SEMI.				{ s->cur_params().lp.font_size = A; }
label_param  ::= TEXT EQ string(A) SEMI.				{ core::strncpy(s->cur_params().lp.text, A.str, MAX_STRING); }
label_params ::= label_param.
label_params ::= label_params label_param.
label_widget_a ::= WIDGET LABEL. { push_params(s); }
label_widget ::= label_widget_a name_opt(A) LBRACE label_params RBRACE. { create_label_widget(A.str, s); }

// panel widget
panel_param ::= common_param.
widget_list ::= widget.
widget_list ::= widget_list COMMA widget.
panel_param ::= WIDGET_LIST EQ LBRACK widget_list RBRACK SEMI.
panel_params ::= panel_param.
panel_params ::= panel_params panel_param.
panel_widget_a ::= WIDGET PANEL. { push_params(s); }
panel_widget ::= panel_widget_a name_opt(A) LBRACE panel_params RBRACE. { create_panel_widget(A.str, s); }


%parse_failure { s->has_error = true;  }
%syntax_error  { s->has_error = true;  }
%include {
	#define MAX_STRING 128
	typedef char string_type[128];
	
	struct vec3 
	{ 
		float x, y, z; 
	};
		
	struct common_params
	{
		vec3 trans, scale;
		bool visible;
	};
	struct button_params
	{
		char image[MAX_STRING];
		char image_h[MAX_STRING];
	};
	struct image_params
	{
		char image[MAX_STRING];		
	};
	struct label_params
	{
		char font[MAX_STRING];
		char text[MAX_STRING];
		int  font_size;
	};
	struct panel_params
	{
		std::vector<ui::widget_ptr> widgets;
	};
	struct all_params
	{
		common_params cp;
		button_params bp;
		image_params  ip;
		label_params  lp;
		panel_params  pp;
	};
	
	void reset_params(all_params &p)
	{
		p.cp.trans.x = p.cp.trans.x = p.cp.trans.x = 0;		
		p.cp.scale.x = p.cp.scale.x = p.cp.scale.x = 1;
		p.cp.visible = true;
		p.bp.image[0] = p.bp.image_h[0] = 0;
		p.pp.widgets.clear();		
	}
	
	const int MaxDepth = 16;
	struct state
	{
		state() :
			io(nullptr),
			ii(nullptr),
			cur_depth(0)
		{
		};

		~state()
		{
			io = nullptr;
			ii = nullptr;
		}
		
		all_params& cur_params() { TYCHO_ASSERT(cur_depth >= 0); return params[cur_depth]; }
        io::interface* io;
		input::interface* ii;
        
		graphics::renderer_ptr renderer;
		bool has_error;
		all_params params[MaxDepth];
		int cur_depth;
	};
	
	char* unquote(char* str)
	{
		if(!str)
			return 0;
		char* res = str;
		++str;
		while(*str	!= '"')
		{
			*(str-1) = *(str);
			++str;
		}
		*(str-1) = 0;
		return res;
	}
	
	void set_common(ui::widget_ptr w, common_params& cp)
	{
		math::srt_transformf trans(math::srt_transformf::create_identity());
		trans.set_translation(math::vector3f(cp.trans.x, cp.trans.y, cp.trans.z));
		trans.set_scale(math::vector3f(cp.scale.x, cp.scale.y, cp.scale.z));
		w->set_transform(trans);
	}
	
	void push_params(state *s)
	{
		++s->cur_depth;
	}
	
	void pop_params(state *s)
	{
		reset_params(s->cur_params());
		--s->cur_depth;
	}
	
	void add_widget(ui::widget_ptr w, state *s)	
	{
		pop_params(s);
		s->cur_params().pp.widgets.push_back(w);
	}
	
	void create_label_widget(const char* name, state *s)
	{	
		common_params &cp = s->cur_params().cp;
		label_params &ip = s->cur_params().lp;
						
		graphics::text::font_ptr font = s->renderer->get_font_manager().open_font(unquote(ip.font));
		ui::label_ptr label(new ui::label(name, s->renderer, font, ip.font_size, core::strlen(ip.text)));
		label->set_text(unquote(ip.text));
		set_common(label, cp);
		add_widget(label, s);
	}
	
	void create_image_widget(const char* name, state *s)
	{
		common_params &cp = s->cur_params().cp;
		image_params &ip = s->cur_params().ip;
		ui::image_ptr image(new ui::image(name, s->renderer, 
        graphics::create_texture_from_file_png(s->io, s->renderer, unquote(ip.image))));
		set_common(image, cp);
		add_widget(image, s);
	}
	
	void create_button_widget(const char* name, state *s)
	{
		common_params &cp = s->cur_params().cp;
		button_params &bp = s->cur_params().bp;
		graphics::texture_ptr tex1, tex2;
		if(bp.image[0])
			tex1 = graphics::create_texture_from_file_png(s->io, s->renderer, unquote(bp.image));
		if(bp.image_h[0])
			tex2 = graphics::create_texture_from_file_png(s->io, s->renderer, unquote(bp.image_h));
		ui::button_ptr button(new ui::button(name, s->renderer, tex1, tex2));
		set_common(button, cp);
		add_widget(button, s);
	}

	void create_panel_widget(const char* name, state *s)
	{
		common_params &cp = s->cur_params().cp;
		panel_params &pp = s->cur_params().pp;
		ui::panel_ptr w(new ui::panel(s->ii, name));
		set_common(w, cp);
		for(size_t i = 0; i < pp.widgets.size(); ++i)
			w->add_widget(pp.widgets[i]);
		add_widget(w, s);		
	}
}
