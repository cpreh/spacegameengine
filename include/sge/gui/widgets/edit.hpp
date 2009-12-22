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


#ifndef SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_EDIT_HPP_INCLUDED

#include <sge/gui/detail/cursor_delegate.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/timer/fwd.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/image.hpp>
#include <sge/gui/export.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class SGE_CLASS_SYMBOL edit : public base
{
public:
	enum line_type { single_line,multi_line };

	SGE_GUI_SYMBOL edit(
		parent_data const &,
		parameters,
		line_type,
		dim const &desired_size);

	SGE_GUI_SYMBOL fcppt::string const text() const;
	SGE_GUI_SYMBOL void text(fcppt::string const &);
	SGE_GUI_SYMBOL point const &scroll_pos() const;
	SGE_GUI_SYMBOL dim const desired_size() const;
	SGE_GUI_SYMBOL image &text_buffer();
	SGE_GUI_SYMBOL image const &text_buffer() const;

	SGE_GUI_SYMBOL void process_keyboard_enter(events::keyboard_enter const &);
	SGE_GUI_SYMBOL key_handling::type process_key(events::key const &);
	SGE_GUI_SYMBOL void process_mouse_click(events::mouse_click const &);
	SGE_GUI_SYMBOL void process_keyboard_leave(events::keyboard_leave const &);

	SGE_GUI_SYMBOL void refresh() const;

	// will only be called for single_line
	fcppt::signal::object<void ()> return_pressed;
private:
	line_type type;
	fcppt::string text_;
	dim desired_size_;
	timer::object_ptr timer_;
	bool cursor_visible_;
	mutable image text_buffer_;
	mutable point scroll_pos_;
	detail::cursor_delegate cursor;

	void blink_callback();
	void resize(dim const &) const;
};
}
}
}

#endif
