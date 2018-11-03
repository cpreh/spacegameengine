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


#include <sge/opengl/texture/check_dim.hpp>
#include <sge/opengl/texture/pp_dims.hpp>
#include <sge/opengl/texture/warn_min.hpp>
#include <sge/opengl/texture/warn_pow2.hpp>
#include <sge/renderer/basic_dim.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/string.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <fcppt/config/external_end.hpp>


template<
	fcppt::math::size_type Size
>
void
sge::opengl::texture::check_dim(
	fcppt::log::object &_log,
	sge::renderer::basic_dim<
		Size
	> const &_dim,
	sge::renderer::size_type const _min_value,
	fcppt::string const &_what
)
{
	sge::opengl::texture::warn_min(
		_log,
		_dim,
		_min_value,
		_what
	);

	sge::opengl::texture::warn_pow2(
		_log,
		_dim,
		_what
	);
}

#define SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM(\
	seq,\
	_,\
	dimension\
)\
template \
void \
sge::opengl::texture::check_dim<\
	dimension\
>(\
	fcppt::log::object &,\
	sge::renderer::basic_dim< \
		dimension \
	> const &, \
	sge::renderer::size_type, \
	fcppt::string const & \
);

BOOST_PP_SEQ_FOR_EACH(
	SGE_OPENGL_TEXTURE_INSTANTIATE_CHECK_DIM,
	_,
	SGE_OPENGL_TEXTURE_PP_DIMS
)
