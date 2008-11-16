/**
\page tut_fonts Font tutorial
\section tut_fonts_abstract Abstract
After a little delay we'll program a simple "hello world" program which uses
components from sge::font to draw this text in the center of the screen. You
should have read the \ref tut_begin "beginners tutorial", I'll make references
to most of it.

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

\section tut_fonts_the_code Initializing
So let's start at the top, the <em>font system</em>. We use our old shortcut sge::systems again to load this system:

\code
sge::systems::instance const sys(
	sge::systems::list()
	(sge::window::parameters(
		SGE_TEXT("sge font tutorial"),
		sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size_t(
					640,
					480),
				sge::renderer::bit_depth::depth32),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed)))
	(sge::systems::parameterless::font));
\endcode

Files to include: <sge/systems/instance.hpp>, <sge/systems/list.hpp>,
<sge/renderer/parameters.hpp>, <sge/window/parameters.hpp>, <sge/text.hpp>.

Since the system doesn't receive any parameters, we can go on to the next
component, the <em>font metrics</em>. As seen in the diagram, we use sge::font::system to load a metric:

\code
sge::font::metrics_ptr const metrics = 
	sys.font_system()->create_font(
		sge::media_path() / SGE_TEXT("fonts") / SGE_TEXT("default.ttf"),
		static_cast<sge::font::size_type>(15));
\endcode

Files to include: <sge/font/metrics.hpp>, <sge/media.hpp>, <sge/text.hpp>

Okay, so sge::font::system has a \link sge::font::system::create_font
create_font \endlink function which returns a \link sge::font::metrics_ptr
metrics_ptr \endlink containing the metric in an internal format. 

sge itself comes with a standard font (an open one, so no copyright
infringements are to be expected) which resides in the "media path" you specify
at compile time. This path is accessed via the sge::media_path() function, which
returns an sge::path. That's the reason you can use <tt>operator/</tt> to
concatenate the path with the string (which, again, is surrounded by the
SGE_TEXT macro).

The second parameter denotes the <em>font size</em>. A value of 15 is nice to
read on a 640x480 display (which we'll initialize next). 

\note Note that we cast to sge::font::size_type since we don't know if this
size_type is integral and if so, which of the integral types it is. Good
compilers will issue a warning if there's no explicit cast here.

\code
sge::font::drawer_ptr const drawer(
	new sge::font::drawer_3d(
		sys.renderer()));
\endcode

Files to include: <sge/font/drawer_3d.hpp>

The statement creates the font drawer. sge::font::font expects a
sge::font::drawer_ptr (which is a smart pointer), so we have to put drawer_3d
inside one. There's no specific reason why sge::font::font is configured that
way, it could also take an sge::font::drawer reference, but that's how it is.

\section tut_fonts_drawing Drawing the text
Now we can create a font and start drawing text. Creating the font is trivial:

\code
sge::font::font font(metrics, drawer);
\endcode

Files to include: <sge/font/font.hpp>

Drawing a text, however, takes a few more lines. sge::font::font::draw_text takes 6 parameters:

<ul>
<li> <tt>text</tt> - The text to be drawn
<li> <tt>pos</tt> - Upper left corner of the bounding rect where the text resides in
<li> <tt>dim</tt> - Size of the bounding rect. If this is too small, the font will be drawn only partially or not at all (for example, if the height is too narrow to fit any character)
<li> <tt>horizontal alignment</tt> - Can be <tt>left, center, right</tt>
<li> <tt>vertical alignment</tt> - Can be <tt>top, center, bottom</tt>
<li> <tt>flags</tt> - Here you can specify that text shouldn't be wrapped (<tt>flags::no_line_wrap</tt>) or that a newline should be ignored (<tt>flags::no_multi_line</tt>).
</ul>

Now that we know, here's the main loop:

\code
while (true)
{
	sge::mainloop::dispatch();
	sge::renderer::scoped_block const block(sys.renderer);
	font.draw_text(
		SGE_TEXT("hello world"),
		sge::font::pos(
			static_cast<sge::font::unit>(0),
			static_cast<sge::font::unit>(0)),
		sge::math::structure_cast<sge::font::unit>(
			sys.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);
}
\endcode

Files to include: <sge/renderer/scoped_block.hpp>,
<sge/mainloop/dispatch.hpp>

This loop, as in the first tutorial, loops forever until you close it somehow.
Feel free to integrate an input system if you like. There's nothing much here
that needs explanation.
The first line tells us that the text should be draw beginning at (0,0) in
pixel coordinates.
The second line tells us that it takes up
the whole screen. <tt>sge::math::structure_cast<T>(x)</tt> is basically just a
shorthand for 

\code
sge::math::dim<T>(static_cast<T>(x.w()),...);
\endcode

since sge::renderer::screen_unit doesn't have to be the same as sge::font::unit.
And that's it, fellas, "hello world" in sge.

\section tut_fonts_final_code The result

The final code looks like this

\include font.cpp
*/
