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


#ifndef SGE_WIN32_WINDOW_HPP_INCLUDED
#define SGE_WIN32_WINDOW_HPP_INCLUDED

#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/signals.hpp>
#include <boost/ptr_container/ptr_map.hpp>

#include "shared_ptr.hpp"
#include "string.hpp"
#include "window.hpp"
#include "export.hpp"
#include "windows.hpp"

namespace sge
{

class win32_window : public window {
public:
	typedef unsigned win32_event_type;
	typedef boost::optional<LRESULT> win32_callback_return_type;

	struct win32_signal_combiner {
		typedef win32_callback_return_type result_type;
		template<typename InputIterator> result_type operator()(InputIterator first, InputIterator last) const
		{
			while (first != last)
			{
				if (*first)
					return **first;
				++first;
			}
			return result_type();
		}
	};

	typedef win32_callback_return_type win32_callback_signature_type(win32_window&, win32_event_type, WPARAM, LPARAM);
	typedef boost::function<win32_callback_signature_type> win32_callback_type;
	typedef boost::signal<win32_callback_signature_type, win32_signal_combiner> win32_signal_type;

	SGE_SYMBOL win32_window(window_size sz, const string& title = string());
	SGE_SYMBOL ~win32_window();

	SGE_SYMBOL void title(const string& t);
	SGE_SYMBOL void size(window_size newsize);
	SGE_SYMBOL window_size size() const;
	SGE_SYMBOL const string& title() const;
	SGE_SYMBOL HWND hwnd() const;
	SGE_SYMBOL boost::signals::connection register_callback(win32_event_type, win32_callback_type);
	SGE_SYMBOL win32_callback_return_type execute_callback(win32_event_type msg, WPARAM wparam, LPARAM lparam);
	SGE_SYMBOL window_pos viewport_offset() const;
private:
	string      _title;
	struct {
		unsigned r, l, t, b;
	} decoration_size;
	HWND        handle;
	static bool wndclass_created;

	typedef boost::ptr_map<win32_event_type, win32_signal_type> win32_signal_map;
	win32_signal_map signals;
};

typedef shared_ptr<win32_window> win32_window_ptr;

}

#endif
