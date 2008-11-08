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


#ifndef SGE_RENDERER_VF_UNSPECIFIED_HPP_INCLUDED
#define SGE_RENDERER_VF_UNSPECIFIED_HPP_INCLUDED

#include "vec_base.hpp"
#include "single_base.hpp"
#include "color_base.hpp"
#include "vertex_size.hpp"
#include "role.hpp"
#include <boost/static_assert.hpp>

namespace boost
{
namespace gil
{

// TODO: move this away!
template<
	typename Channel,
	typename Layout
> class pixel;

}
}

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format,
	vertex_size NumSubElements
>
struct unspecified
: vec_base<
	Format,
	role::unspecified,
	NumSubElements
> {
	BOOST_STATIC_ASSERT(
		NumSubElements >= 2 && NumSubElements <= 4);
};

template<
	typename Format
>
struct unspecified<
	Format,
	1
>
: single_base<
	Format,
	role::unspecified
> {};

template<
	typename Channel,
	typename Layout
>
struct unspecified
: color_base<
	boost::gil::pixel<
		Channel,
		Layout
	>,
	role::unspecified
> {};

}
}
}

#endif
