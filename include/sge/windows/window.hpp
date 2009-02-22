/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)
Copyright (C) 2007       Simon Stienen    (s.stienen@slashlife.org)

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
#include <sge/windows/windows.hpp>
#include <sge/windows/wndclass_fwd.hpp>
#include <sge/string.hpp>
#include <sge/window/instance.hpp>
#include <sge/export.hpp>
#include <sge/signals/connection.hpp>
#include <sge/signals/signal.hpp>
#include <sge/math/rect_decl.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/ptr_container/ptr_map.hpp>

namespace sge
{
namespace windows
{

class window : public sge::window::instance {
public:
	typedef unsigned event_type;
	typedef boost::optional<LRESULT> callback_return_type;

	//struct signal_combiner;

	typedef callback_return_type
	callback_signature_type(
		window &,
		event_type,
		WPARAM,
		LPARAM);

	typedef boost::function<
		callback_signature_type
	> callback_type;

	typedef signals::signal<
		callback_signature_type//,
	//	signal_combiner
	> signal_type;

	SGE_SYMBOL window(
		dim_type const &sz,
		sge::string const &title,
		sge::string const &class_name);
	SGE_SYMBOL ~window();

	SGE_SYMBOL void title(sge::string const &t);
	SGE_SYMBOL void size(dim_type const &newsize);
	SGE_SYMBOL window::dim_type const size() const;
	SGE_SYMBOL sge::string const title() const;
	SGE_SYMBOL HWND hwnd() const;
	SGE_SYMBOL signals::connection
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

	typedef math::rect<
		unsigned
	> decoration_rect;

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
