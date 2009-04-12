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


#ifndef SGE_PARSE_JSON_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_VALUE_HPP_INCLUDED

#include <sge/parse/json/string.hpp>
#include <sge/parse/json/null.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

namespace sge
{
namespace parse
{
namespace json
{

struct array;
struct object;

typedef boost::variant<
	boost::recursive_wrapper<
		object
	>,
	boost::recursive_wrapper<
		array
	>,
	bool,
	string,
	double,
	int,
	null
> value;

}
}
}

#endif
