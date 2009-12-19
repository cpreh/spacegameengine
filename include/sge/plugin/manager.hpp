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


#ifndef SGE_PLUGIN_MANAGER_HPP_INCLUDED
#define SGE_PLUGIN_MANAGER_HPP_INCLUDED

#include <sge/plugin/capabilities.hpp>
#include <sge/plugin/category_array.hpp>
#include <sge/export.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>
#include <map>
#include <cstddef>

namespace sge
{
namespace plugin
{

class context_base;

template<typename T>
class context;

template<typename T>
class iterator;

class manager {
	typedef std::vector<context_base> plugin_array;
	typedef std::map<capabilities::type, category_array> plugin_map;

	FCPPT_NONCOPYABLE(manager)
public:
	typedef std::size_t size_type;

	SGE_SYMBOL manager();
	SGE_SYMBOL ~manager();

	template<typename T>
	SGE_SYMBOL iterator<T> begin();

	template<typename T>
	SGE_SYMBOL iterator<T> end();

	template<typename T>
	SGE_SYMBOL context<T>
	plugin(
		size_type index = 0);

	template<typename T>
	SGE_SYMBOL size_type size() const;
private:
	plugin_array plugins;
	plugin_map categories;
};

}
}

#endif
