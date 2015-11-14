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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/address/make_actors.hpp>
#include <sge/opengl/state/core/sampler/filter/make_actors.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <fcppt/algorithm/join.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::make_actors(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::core::sampler::address::make_actors(
				_parameters.address()
			),
			sge::opengl::state::core::sampler::filter::make_actors(
				_context,
				_parameters.filter()
			)
		);
}
