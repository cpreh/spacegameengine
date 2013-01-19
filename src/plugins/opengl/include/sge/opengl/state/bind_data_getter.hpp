/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_STATE_BIND_DATA_GETTER_HPP_INCLUDED
#define SGE_OPENGL_STATE_BIND_DATA_GETTER_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <boost/phoenix/core/value.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename Type
>
std::function<
	typename Type::const_pointer ()
> const
bind_data_getter(
	Type const &_value
)
{
	return
		boost::phoenix::bind(
			static_cast<
				typename Type::const_pointer
				(Type::*)() const
			>(
				&Type::data
			),
			boost::phoenix::val(
				_value
			)
		);
}

}
}
}

#endif
