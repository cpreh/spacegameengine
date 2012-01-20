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


#ifndef SGE_SPRITE_RENDER_ONE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_ONE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_single_range.hpp>
#include <sge/sprite/render/geometry_options.hpp>
#include <sge/sprite/render/is_options.hpp>
#include <sge/sprite/render/with_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace render
{

template<
	typename Options,
	typename Choices,
	typename Buffers
>
typename boost::enable_if<
	sge::sprite::render::is_options<
		Options
	>,
	void
>::type
one_with_options(
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers
)
{
	BOOST_STATIC_ASSERT(
		Options::geometry_options
		!= sge::sprite::render::geometry_options::sort_and_fill
	);

	sge::sprite::render::with_options<
		Options
	>(
		sge::sprite::geometry::make_single_range(
			_sprite
		),
		_buffers,
		sge::sprite::compare::nothing()
	);
}

}
}
}

#endif
