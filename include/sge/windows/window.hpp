/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_WINDOWS_WINDOW_HPP_INCLUDED
#define SGE_WINDOWS_WINDOW_HPP_INCLUDED

#include <sge/windows/window_fwd.hpp>
#include <sge/windows/callback_return_type.hpp>
#include <sge/windows/event_type.hpp>
#include <sge/windows/windows.hpp>
#include <sge/windows/wndclass_ptr.hpp>
#include <sge/window/instance.hpp>
#include <sge/symbol.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/box/basic_decl.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional_fwd.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace windows
{

class window : public sge::window::instance {
public:
	typedef callback_return_type
	callback_signature_type(
		window &,
		event_type,
		WPARAM,
		LPARAM);

	typedef fcppt::function::object<
		callback_signature_type
	> callback_type;

	typedef fcppt::signal::object<
		callback_signature_type
	> signal_type;

	SGE_SYMBOL window(
		dim_type const &sz,
		fcppt::string const &title,
		fcppt::string const &class_name);
	SGE_SYMBOL ~window();

	SGE_SYMBOL void title(fcppt::string const &t);
	SGE_SYMBOL void size(dim_type const &newsize);
	SGE_SYMBOL window::dim_type const size() const;
	SGE_SYMBOL fcppt::string const title() const;
	SGE_SYMBOL HWND hwnd() const;
	SGE_SYMBOL fcppt::signal::auto_connection
	register_callback(
		event_type,
		callback_type);
	SGE_SYMBOL callback_return_type
	execute_callback(
		event_type msg,
		WPARAM wparam,
		LPARAM lparam);
	SGE_SYMBOL pos_type const viewport_offset() const;

	SGE_SYMBOL void dispatch();
private:
	wndclass_ptr const wndclass_;

	typedef fcppt::math::box::rect<
		LONG
	>::type decoration_rect;

	decoration_rect decoration_size;
	HWND        handle;

	typedef boost::ptr_map<
		event_type,
		signal_type
	> signal_map;

	signal_map signals;
};

}
}

#endif
