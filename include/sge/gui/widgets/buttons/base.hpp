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


#ifndef SGE_GUI_WIDGETS_BUTTONS_BASE_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_BASE_HPP_INCLUDED

#include <sge/gui/widgets/base.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/signal/object.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{

class SGE_CLASS_SYMBOL base : public widgets::base
{
public:
	SGE_GUI_SYMBOL bool mouse_over() const;
	SGE_GUI_SYMBOL bool key_over() const;

	SGE_GUI_SYMBOL void process(events::mouse_enter const &);
	SGE_GUI_SYMBOL void process(events::mouse_leave const &);
	SGE_GUI_SYMBOL void process(events::mouse_click const &);
	SGE_GUI_SYMBOL void process(events::keyboard_enter const &);
	SGE_GUI_SYMBOL key_handling::type process(events::key const &);
	SGE_GUI_SYMBOL void process(events::keyboard_leave const &);
	using widgets::base::process;

	typedef boost::function<void ()> clicked_fn;
	SGE_GUI_SYMBOL signal::auto_connection register_clicked(
		clicked_fn const &);
	
	SGE_GUI_SYMBOL ~base();
private:

	bool mouse_over_;
	bool key_over_;
	sge::signal::object<void ()> clicked_;
protected:
	SGE_GUI_SYMBOL base(
		parent_data const &,
		parameters);
};

}
}
}
}

#endif
