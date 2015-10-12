/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/texture/instantiate_dim.hpp>
#include <sge/opengl/texture/mipmap/get_levels.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/levels_rep.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/texture/mipmap/off_rep_fwd.hpp>
#include <sge/renderer/texture/mipmap/variant.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/log2.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Size
>
sge::renderer::texture::mipmap::level_count
sge::opengl::texture::mipmap::get_levels(
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::basic_dim<
		Size
	> const &_dim
)
{
	return
		fcppt::variant::match(
			_mipmap.variant(),
			[](
				sge::renderer::texture::mipmap::off_rep const &
			)
			{
				return
					sge::renderer::texture::mipmap::level_count(
						1u
					);
			},
			[
				&_dim
			](
				sge::renderer::texture::mipmap::all_levels_rep const &
			)
			{
				return
					fcppt::strong_typedef_construct_cast<
						sge::renderer::texture::mipmap::level_count,
						fcppt::cast::size_fun
					>(
						1u
						+
						fcppt::math::log2(
							*boost::range::max_element(
								_dim.storage()
							)
						)
					);
			},
			[](
				sge::renderer::texture::mipmap::levels_rep const &_levels
			)
			{
				return
					_levels.value();
			}
		);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GET_LEVELS(\
	dimension\
)\
template \
sge::renderer::texture::mipmap::level_count \
sge::opengl::texture::mipmap::get_levels<\
	dimension\
>(\
	sge::renderer::texture::mipmap::object const &,\
	sge::renderer::basic_dim<\
		dimension\
	> const &\
)

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_GET_LEVELS
);
