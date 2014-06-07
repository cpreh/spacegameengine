/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/ffp/sampler/actor.hpp>
#include <sge/opengl/state/ffp/sampler/set_one.hpp>
#include <sge/opengl/texture/funcs/env_arg.hpp>
#include <sge/opengl/texture/funcs/env_int.hpp>
#include <sge/opengl/texture/funcs/env_int_value.hpp>
#include <sge/opengl/texture/funcs/env_target.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::ffp::sampler::actor
sge::opengl::state::ffp::sampler::set_one(
	sge::opengl::texture::funcs::env_arg const _arg,
	sge::opengl::texture::funcs::env_int_value const _value
)
{
	return
		std::bind(
			sge::opengl::texture::funcs::env_int,
			std::placeholders::_1,
			fcppt::strong_typedef_construct_cast<
				sge::opengl::texture::funcs::env_target
			>(
				GL_TEXTURE_ENV
			),
			_arg,
			_value
		);
}
