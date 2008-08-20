/**
\page tut_fonts Font tutorial
\section tut_fonts_preface Preface
The font system in sge is split up into subcomponents, all of them residing in
the sge::font namespace: 

There's the <em>font system</em> which loads fonts from memory or from an
external source; in most cases, those fonts will be true type (.ttf) fonts
located on your disc.

More specifically, the font system loads a <em>font metric</em>. As the name
suggests, a font metric contains information about the size and the looks of
the particular font. sge currently uses freetype to load those metrics.

Drawing the font onto some canvas is separated from the loading. The <em>font
drawer</em> is responsible for that. 

The glue between the metric and the drawer is the sge::font::font class. It's
responsible for things such as text alignment and managing special characters
like a newline sensibly.

\dot 
digraph font_graph
{
	node [fontsize=10]
	edge [fontsize=10]
	font_system [label="font::system",shape=box,URL="\ref sge::font::system"]
	font_metrics [label="font::metrics",shape=box,URL="\ref sge::font::metrics"]
	font_drawer [label="font::drawer",shape=box URL="\ref sge::font::drawer"]
	font_font [label="font::font",shape=box URL="\ref sge::font::font"]

	screen [label="screen",style=dashed]
	texture [label="texture",style=dashed]

	text [label="text to draw",style=dashed]

	text -> font_font [style=dashed]

	font_drawer -> screen [style=dashed]
	font_drawer -> texture [style=dashed]

	font_system -> font_metrics [label="  loads"]
	font_metrics -> font_font [label="is passed to"]
	font_drawer -> font_font [label="  is passed to"]
	font_font -> font_drawer [label="passes info"]
}
\enddot

\section tut_fonts_the_code The Code
So let's start at the top, the <em>font system</em>. 
*/
