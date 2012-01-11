/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_RENDER_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_DEFAULT_GEOMETRY_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/render/do_default_sort.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Choices,
	typename Compare,
	typename Enable = void
>
struct default_geometry_options;

template<
	typename Choices,
	typename Compare
>
struct default_geometry_options<
	Choices,
	Compare,
	typename boost::enable_if<
		sge::sprite::detail::render::do_default_sort<
			Choices,
			Compare
		>
	>::type
>
:
boost::mpl::integral_c<
	sge::sprite::render::geometry_options::type,
	sge::sprite::render::geometry_options::sort_and_fill
>
{
};

template<
	typename Choices,
	typename Compare
>
struct default_geometry_options<
	Choices,
	Compare,
	typename boost::disable_if<
		sge::sprite::detail::render::do_default_sort<
			Choices,
			Compare
		>
	>::type
>
:
boost::mpl::integral_c<
	sge::sprite::render::geometry_options::type,
	sge::sprite::render::geometry_options::fill
>
{
};

}
}
}

#endif
