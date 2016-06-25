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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/sampler/context.hpp>
#include <sge/opengl/state/ffp/sampler/default_context.hpp>
#include <sge/opengl/state/ffp/sampler/object.hpp>
#include <sge/opengl/state/ffp/sampler/set_defaults.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::opengl::state::ffp::sampler::set_defaults(
	sge::opengl::context::object &_context
)
{
	// Samplers are always active in every stage and we must make sure that
	// the defaults are restored everywhere.

	fcppt::optional::maybe_void(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_context,
			_context.info()
		).config(),
		[
			&_context
		](
			sge::opengl::texture::multi_config const &_config
		)
		{
			sge::opengl::state::ffp::sampler::object const &default_state(
				sge::opengl::context::use<
					sge::opengl::state::ffp::sampler::default_context
				>(
					_context
				).default_state()
			);

			sge::opengl::context::use<
				sge::opengl::state::ffp::sampler::context
			>(
				_context
			).stages(
				sge::renderer::texture::stage(
					0u
				)
			);

			for(
				sge::renderer::texture::stage const stage
				:
				fcppt::make_int_range_count(
					sge::renderer::texture::stage{
						_config.max_level().get()
					}
				)
			)
			{
				sge::opengl::texture::active_level const active_level(
					_context,
					stage
				);

				default_state.set(
					active_level
				);
			}
		}
	);
}
