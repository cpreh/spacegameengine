/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <cstddef>
#include <vector>
#include <map>
#include <iterator>
#include <boost/noncopyable.hpp>
#include <boost/weak_ptr.hpp>
#include "path.hpp"
#include "shared_ptr.hpp"
#include "plugin.hpp"
#include "string.hpp"
#include "exception.hpp"
#include "export.hpp"
#include "iconv.hpp"
#include "text.hpp"

namespace sge
{
namespace plugin
{

class manager : boost::noncopyable {
	typedef std::vector<context_base> plugin_array;
	typedef std::vector<context_base*> category_array;
	typedef std::map<type::type, category_array> plugin_map;
public:
	typedef std::size_t size_type;

	SGE_SYMBOL manager();

	template<typename T>
	iterator<T> begin();

	template<typename T>
	iterator<T> end();

	template<typename T>
	typename iterator<T>::reference get_plugin(
		size_type index = 0);

	template<typename T>
	size_type size() const;
private:
	plugin_array plugins;
	plugin_map categories;
};

}

#endif
