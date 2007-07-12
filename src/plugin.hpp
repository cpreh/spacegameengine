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


#ifndef SGE_PLUGIN_HPP_INCLUDED
#define SGE_PLUGIN_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "string.hpp"
#include "shared_ptr.hpp"
#include "plugin_traits.hpp"
#include "library.hpp"

namespace sge
{

struct plugin_info {
	plugin_info()
	 : name(0), description(0), plugin_version(0), min_core_version(0), type(PT_Nothing)
	{}

	const char*  name;
	const char*  description;
	unsigned     plugin_version;
	unsigned     min_core_version;
	plugin_type  type;
};

struct plugin_base {
	virtual ~plugin_base(){}
};

template<typename T>
class plugin : boost::noncopyable, public plugin_base {
public:
	typedef typename detail::plugin_traits<T>::loader_fun loader_fun;
	typedef shared_ptr<plugin<T> > ptr_type;

	plugin(const std::string& path)
	: lib(path),
	  loader(lib.load_function<loader_fun>(detail::plugin_traits<T>::plugin_loader_name()))
	{}

	loader_fun get() const
	{
		return loader;
	}
private:
	library lib;
	const loader_fun loader;
};

}

#endif

