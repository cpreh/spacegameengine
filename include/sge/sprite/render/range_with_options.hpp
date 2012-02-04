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


#ifndef SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_RENDER_RANGE_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/buffers/parameters.hpp>
#include <sge/sprite/detail/render/matrices.hpp>
#include <sge/sprite/detail/render/range.hpp>
#include <sge/sprite/detail/render/scoped_states.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/render/is_options.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <fcppt/config/external_begin.hpp>
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
	typename Choices
>
typename boost::enable_if<
	sge::sprite::render::is_options<
		Options
	>,
	void
>::type
range_with_options(
	sge::sprite::buffers::parameters const &_parameters,
	sge::sprite::render::range<
		Choices
	> const &_range
)
{
	if(
		_range.empty()
	)
		return;

	sge::sprite::detail::render::matrices<
		Options::matrix_options
	>(
		_parameters.renderer()
	);

	sge::sprite::detail::render::scoped_states<
		Choices,
		Options::state_options
	> const states(
		_parameters.renderer()
	);

	sge::sprite::detail::render::scoped_vertex<
		Options::vertex_options
	> const vertex(
		_parameters,
		_range.vertex_buffer()
	);

	sge::sprite::detail::render::range(
		_parameters.renderer(),
		_range
	);
}

}
}
}

#endif
