/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/mipmap/all_levels.hpp>
#include <sge/opengl/texture/mipmap/create.hpp>
#include <sge/opengl/texture/mipmap/levels.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Dim
>
void
sge::opengl::texture::mipmap::create(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::opengl::texture::mipmap::parameters<
		Dim
	> const &_parameters,
	sge::renderer::texture::mipmap::object const &_mipmap
)
{
	fcppt::variant::match(
		_mipmap.variant(),
		[](
			sge::renderer::texture::mipmap::off_rep const &
		)
		{
		},
		[
			&_log,
			&_context,
			&_parameters
		](
			sge::renderer::texture::mipmap::all_levels_rep const &_all_levels
		)
		{
			sge::opengl::texture::mipmap::all_levels(
				_log,
				_context,
				_parameters,
				_all_levels
			);
		},
		[
			&_log,
			&_context,
			&_parameters
		](
			sge::renderer::texture::mipmap::levels_rep const &_levels
		)
		{
			sge::opengl::texture::mipmap::levels(
				_log,
				_context,
				_parameters,
				_levels
			);
		}
	);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE(\
	seq,\
	_,\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::create<\
	dimension\
>(\
	fcppt::log::object &, \
	sge::opengl::context::object &, \
	sge::opengl::texture::mipmap::parameters< \
		dimension \
	> const &, \
	sge::renderer::texture::mipmap::object const &\
)

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
