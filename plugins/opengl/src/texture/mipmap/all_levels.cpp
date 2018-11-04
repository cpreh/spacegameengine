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
#include <sge/opengl/texture/mipmap/auto_generate.hpp>
#include <sge/opengl/texture/mipmap/generate_levels.hpp>
#include <sge/opengl/texture/mipmap/parameters.hpp>
#include <sge/renderer/texture/mipmap/all_levels_rep.hpp>
#include <sge/renderer/texture/mipmap/auto_generate.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::mipmap::all_levels(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::opengl::texture::mipmap::parameters<
		Size
	> const &_parameters,
	sge::renderer::texture::mipmap::all_levels_rep const &_rep
)
{
	if(
		_rep.auto_generate()
		==
		sge::renderer::texture::mipmap::auto_generate::yes
	)
		sge::opengl::texture::mipmap::auto_generate(
			_log,
			_parameters.binding(),
			_context
		);
	else
		sge::opengl::texture::mipmap::generate_levels(
			_parameters,
			sge::renderer::texture::mipmap::level_count(
				std::numeric_limits<
					sge::renderer::texture::mipmap::level_count::value_type
				>::max()
			)
		);
}

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_ALL_LEVELS(\
	seq,\
	_,\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::all_levels<\
	dimension\
>(\
	fcppt::log::object &,\
	sge::opengl::context::object &,\
	sge::opengl::texture::mipmap::parameters<\
		dimension\
	> const &,\
	sge::renderer::texture::mipmap::all_levels_rep const &\
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_ALL_LEVELS,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
