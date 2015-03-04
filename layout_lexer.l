/*****************************************************************************
// Tycho Game Library
// Copyright (C) 2008 Martin Slater
// Created : Wednesday, 21 May 2008 11:27:02 PM
//    
// Flex lexer spec for ui layout file
// THIS MUST USE UNIX STYLE LINE ENDINGS - if flex crashes you're editor
// probably mangled them to windows style.
*****************************************************************************/
%option c++
%option noyywrap
%option yylineno
%{
int line = 0;
int frcol = 0;
int tocol = 0;
#define YY_USER_ACTION { frcol = tocol; tocol += yyleng; }
#define RETURN_TOKEN(_tok) return _tok;
%}
ALPHACHAR		[a-zA-Z_]
ID				{ALPHACHAR}+{DIGIT}*
NEWLINE			[\n] 
HEXDIGIT	    [0-9a-fA-F]
OCTESCAPE	    \\[0-7]{1,3}
HEXESCAPE	    \\x{HEXDIGIT}+
UNIV		    \\u{HEXDIGIT}{4}|\\U{HEXDIGIT}{8}
ESCAPE              (\\[ntvbrfa\n\\?'"])|{OCTESCAPE}|{HEXESCAPE}|{UNIV}
WHITESPACE	    {WSCHAR}+|({WSCHAR}*\\{NEWLINE})+{WSCHAR}*
DIGIT		    [0-9]
NUMBER		    [+-]?{DIGIT}+
STRING          \"([^\\\n"]|{ESCAPE})*\" 
EXPONENT	    [Ee][+-]?[0-9]+
FRACTIONAL	    ([0-9]+\.)|([0-9]*\.[0-9]+)
DECFLOAT	    {FRACTIONAL}{EXPONENT}?|[0-9]+{EXPONENT}
%%
{NEWLINE} { line++; frcol = tocol = 0; } 

	/* keywords */
widget	{ RETURN_TOKEN(TY_WIDGET); }
version { RETURN_TOKEN(TY_VERSION); }
true    { RETURN_TOKEN(TY_TRUE); }
false   { RETURN_TOKEN(TY_FALSE); }

	/* widget types */
button	{ RETURN_TOKEN(TY_BUTTON); }
image   { RETURN_TOKEN(TY_IMAGE); }
label   { RETURN_TOKEN(TY_LABEL); }
panel   { RETURN_TOKEN(TY_PANEL); }

	/* parameter names */
trans   { RETURN_TOKEN(TY_TRANS); }
scale   { RETURN_TOKEN(TY_SCALE); }
visible { RETURN_TOKEN(TY_VISIBLE); }
image   { RETURN_TOKEN(TY_IMAGE); }
image_h { RETURN_TOKEN(TY_IMAGE_H); }
font    { RETURN_TOKEN(TY_FONT); }
font_size { RETURN_TOKEN(TY_FONT_SIZE); }
text    { RETURN_TOKEN(TY_TEXT); }
widget_list { RETURN_TOKEN(TY_WIDGET_LIST); }

	/* literals */
{NUMBER}   { RETURN_TOKEN(TY_INT); }
{STRING}   { RETURN_TOKEN(TY_STRING); }
{DECFLOAT} { RETURN_TOKEN(TY_FLOAT); }
{ID}       { RETURN_TOKEN(TY_ID); }

	/* misc */
"{" { RETURN_TOKEN(TY_LBRACE); }
"}" { RETURN_TOKEN(TY_RBRACE); }	
"[" { RETURN_TOKEN(TY_LBRACK); }
"]" { RETURN_TOKEN(TY_RBRACK); }
"=" { RETURN_TOKEN(TY_EQ); }
";" { RETURN_TOKEN(TY_SEMI); }
"," { RETURN_TOKEN(TY_COMMA); }
%%
