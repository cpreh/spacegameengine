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


#ifndef SGE_SPRITE_PROCESS_WITH_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_WITH_OPTIONS_HPP_INCLUDED

#include <sge/sprite/detail/process/geometry.hpp>
#include <sge/sprite/process/is_options.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename Options,
	typename Range,
	typename Buffers,
	typename Compare
>
typename boost::enable_if<
	sge::sprite::process::is_options<
		Options
	>,
	void
>::type
with_options(
	Range const &_range,
	Buffers &_buffers,
	Compare const &_compare
)
{
	sge::sprite::render::range_with_options<
		typename Options::render_options
	>(
		_buffers.parameters(),
		sge::sprite::detail::process::geometry<
			Options::geometry_options,
			typename Buffers::choices
		>(
			_range,
			_buffers,
			_compare
		)
	);
}

}
}
}

#endif
