/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/convert/mag_filter.hpp>
#include <sge/opengl/state/convert/min_filter.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/normal.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::core::sampler::actor_vector const
sge::opengl::state::core::sampler::filter::normal(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::state::core::sampler::filter::normal::parameters const &_filter
)
{
	sge::opengl::state::core::sampler::actor_vector result(
		sge::opengl::state::core::sampler::actor_vector{
			std::bind(
				sge::opengl::texture::funcs::parameter_int,
				std::placeholders::_1,
				GL_TEXTURE_MAG_FILTER,
				static_cast<
					GLint
				>(
					sge::opengl::state::convert::mag_filter(
						_filter.mag()
					)
				)
			),
			std::bind(
				sge::opengl::texture::funcs::parameter_int,
				std::placeholders::_1,
				GL_TEXTURE_MIN_FILTER,
				static_cast<
					GLint
				>(
					sge::opengl::state::convert::min_filter(
						_filter.min(),
						_filter.mip()
					)
				)
			)
		}
	);

	sge::opengl::optional_enum const anisotropy_flag(
		sge::opengl::context::use<
			sge::opengl::state::core::sampler::filter::anisotropy_context
		>(
			_system_context
		).anisotropy_flag()
	);

	if(
		anisotropy_flag
	)
		result.push_back(
			std::bind(
				sge::opengl::texture::funcs::parameter_int,
				std::placeholders::_1,
				*anisotropy_flag,
				1
			)
		);

	return
		result;
}
