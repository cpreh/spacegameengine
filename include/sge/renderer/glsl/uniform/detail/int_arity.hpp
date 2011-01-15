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


#ifndef SGE_RENDERER_GLSL_UNIFORM_DETAIL_INT_ARITY_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_DETAIL_INT_ARITY_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/int_value_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/static_assert.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{
namespace detail
{

template<
	size_type Arity
>
struct int_arity
:
boost::mpl::integral_c<
	int_value_type::type,
	static_cast<
		int_value_type::type
	>(
		Arity - 1
	)
>
{
	BOOST_STATIC_ASSERT(
		Arity >= 1
		&& Arity <= 4
	);
};

}
}
}
}
}

#endif
