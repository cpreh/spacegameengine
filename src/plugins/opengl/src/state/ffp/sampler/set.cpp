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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/ffp/sampler/context.hpp>
#include <sge/opengl/state/ffp/sampler/default_context.hpp>
#include <sge/opengl/state/ffp/sampler/object.hpp>
#include <sge/opengl/state/ffp/sampler/set.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>


void
sge::opengl::state::ffp::sampler::set(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::state::ffp::sampler::const_object_ref_vector const &_samplers
)
{
	sge::renderer::texture::stage const count(
		fcppt::strong_typedef_construct_cast<
			sge::renderer::texture::stage
		>(
			_samplers.size()
		)
	);

	for(
		sge::renderer::texture::stage stage(
			0u
		);
		stage < count;
		++stage
	)
	{
		sge::opengl::texture::active_level const active_level(
			_system_context,
			stage
		);

		static_cast<
			sge::opengl::state::ffp::sampler::object const &
		>(
			_samplers[
				stage.get()
			].get()
		).set(
			active_level
		);
	}

	sge::opengl::state::ffp::sampler::object const &default_state(
		sge::opengl::context::use<
			sge::opengl::state::ffp::sampler::default_context
		>(
			_system_context
		).default_state()
	);

	sge::opengl::state::ffp::sampler::context &context(
		sge::opengl::context::use<
			sge::opengl::state::ffp::sampler::context
		>(
			_device_context
		)
	);

	for(
		sge::renderer::texture::stage stage(
			count
		);
		stage < context.stages();
		++stage
	)
	{
		sge::opengl::texture::active_level const active_level(
			_system_context,
			stage
		);

		default_state.set(
			active_level
		);
	}

	context.stages(
		count
	);
}
