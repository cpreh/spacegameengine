/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/parse/json/array_fwd.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/null.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/string.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/variant/recursive.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


#if 0
namespace boost
{
namespace spirit
{
namespace traits
{

template<
	typename Elements,
	typename Domain
>
struct variant_which<
	fcppt::variant::object<
		Elements
	>,
	Domain
>{
	static int
	call(
		fcppt::variant::object<
			Elements
		> const &_variant
	)
	{
		return
			static_cast<
				int
			>(
				_variant.type_index()
			);
	}
};

}
}
}
#endif

namespace sge
{
namespace parse
{
namespace json
{

typedef fcppt::variant::object<
	boost::mpl::vector7<
		fcppt::variant::recursive<
			json::object
		>,
		fcppt::variant::recursive<
			json::array
		>,
		bool,
		json::string,
		json::float_type,
		json::int_type,
		json::null
	>
> value;

}
}
}

#endif
