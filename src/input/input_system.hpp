/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/signal.hpp>
#include <boost/signals/connection.hpp>
#include <boost/function.hpp>
#include "../shared_ptr.hpp"
#include "../window.hpp"
#include "../plugin_traits.hpp"
#include "key_type.hpp"

namespace sge
{

class input_system : boost::noncopyable {
public:
	typedef void key_pair_fun (const key_pair&);
	typedef boost::signal<key_pair_fun> signal_type;
	typedef boost::function<key_pair_fun> callback;

	typedef void key_type_fun (const key_type&);
	typedef boost::signal<key_type_fun> repeat_signal_type;
	typedef boost::function<key_type_fun> repeat_callback;

	virtual boost::signals::connection register_callback(const callback& c) = 0;
	virtual boost::signals::connection register_repeat_callback(const repeat_callback& c) = 0;
	virtual void dispatch() = 0;

	virtual window_ptr get_window() const = 0;

	virtual ~input_system() {}
};
typedef shared_ptr<input_system> input_system_ptr;

namespace detail
{

template<> struct plugin_traits<input_system> {
	static const char* plugin_loader_name() { return "create_input_system"; }
	static plugin_type::type get_plugin_type() { return plugin_type::input; }
	typedef input_system* (*loader_fun)(window_ptr);
};

}

}

#endif
