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


#include <sge/opengl/state/convert/address_mode.hpp>
#include <sge/opengl/state/convert/address_mode_type.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/address/make_actors.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Mode
>
sge::opengl::state::core::sampler::actor const
set_one(
	Mode
);

}

sge::opengl::state::core::sampler::actor_vector const
sge::opengl::state::core::sampler::address::make_actors(
	sge::renderer::state::core::sampler::address::parameters const &_parameters
)
{
	return
		sge::opengl::state::core::sampler::actor_vector{
			set_one(
				_parameters.mode_s()
			),
			set_one(
				_parameters.mode_t()
			),
			set_one(
				_parameters.mode_t()
			)
		};
}

namespace
{

template<
	typename Mode
>
sge::opengl::state::core::sampler::actor const
set_one(
	Mode const _mode
)
{
	return
		std::bind(
			sge::opengl::texture::funcs::parameter_int,
			std::placeholders::_1,
			sge::opengl::state::convert::address_mode_type<
				Mode
			>::get(),
			sge::opengl::state::convert::address_mode(
				_mode.get()
			)
		);
}

}
