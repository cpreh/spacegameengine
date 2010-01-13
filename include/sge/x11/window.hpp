/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_X11_WINDOW_HPP_INCLUDED
#define SGE_X11_WINDOW_HPP_INCLUDED

#include <sge/x11/display_ptr.hpp>
#include <sge/x11/visual_ptr.hpp>
#include <sge/x11/colormap_ptr.hpp>
#include <sge/x11/wm_hints.hpp>
#include <sge/x11/size_hints.hpp>
#include <sge/x11/class_hint.hpp>
#include <sge/window/instance.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/string.hpp>
#include <X11/Xlib.h>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace x11
{

class SGE_CLASS_SYMBOL window
:
	public sge::window::instance
{
public:
	typedef int event_type;
	typedef long event_mask_type;

	typedef void function_type(XEvent const &);
	typedef fcppt::function::object<function_type> callback_type;

	SGE_SYMBOL window(
		pos_type const &,
		dim_type const &,
		fcppt::string const &title,
		display_ptr,
		int screen,
		int depth,
		bool fullscreen,
		const_visual_ptr,
		colormap_ptr,
		fcppt::string const &class_name
	);

	SGE_SYMBOL ~window();

	SGE_SYMBOL void
	title(
		fcppt::string const &
	);

	SGE_SYMBOL void
	size(
		dim_type const &
	);

	SGE_SYMBOL dim_type const
	size() const;

	SGE_SYMBOL pos_type const
	viewport_offset() const;

	SGE_SYMBOL bool
	fullscreen() const;

	SGE_SYMBOL Window
	get() const;

	SGE_SYMBOL int
	screen() const;

	SGE_SYMBOL display_ptr const
	display() const;

	SGE_SYMBOL const_visual_ptr const
	visual() const;

	SGE_SYMBOL void
	map();

	SGE_SYMBOL void
	map_raised();

	SGE_SYMBOL fcppt::signal::auto_connection
	register_callback(
		event_type,
		callback_type const &
	);

	SGE_SYMBOL void
	dispatch();
private:
	Display *dsp_() const;

	void
	add_event_mask(
		event_type
	);

	void
	hints();

	void
	set_size_hints();

	void
	set_class_hint();

	display_ptr         dsp;
	const_visual_ptr    visual_;
	const_colormap_ptr  colormap_;
	int                 screen_;
	Window              wnd;
	bool                fullscreen_;
	event_mask_type     event_mask;
	wm_hints            hints_;
	size_hints          size_hints_;
	class_hint          class_hint_;

	typedef fcppt::signal::object<
		function_type
	> signal_type;

	typedef boost::ptr_map<
		event_type,
		signal_type
	> signal_map;

	signal_map signals;
};

}
}

#endif
