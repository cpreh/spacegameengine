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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/state/core/sampler/default.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/static_cast.hpp>


sge::opengl::state::core::sampler::context::context(
	sge::opengl::state::core::sampler::context::parameter _context
)
:
	sge::opengl::context::base(),
	defaults_(
		fcppt::make_unique_ptr<
			sge::opengl::state::core::sampler::object
		>(
			sge::opengl::state::core::sampler::make_actors(
				_context,
				sge::renderer::state::core::sampler::default_()
			)
		)
	),
	objects_()
{
}

sge::opengl::state::core::sampler::context::~context()
{
}

void
sge::opengl::state::core::sampler::context::set(
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_samplers
)
{
	for(
		auto const &sampler
		:
		_samplers
	)
	{
		objects_[
			sampler.first
		] =
			fcppt::optional::static_cast_<
				sge::opengl::state::core::sampler::object const
			>(
				sampler.second
			);
	}
}

sge::opengl::state::core::sampler::object const &
sge::opengl::state::core::sampler::context::get(
	sge::renderer::texture::stage const _stage
) const
{
	return
		fcppt::optional::from(
			fcppt::optional::join(
				fcppt::optional::copy_value(
					fcppt::container::find_opt_mapped(
						objects_,
						_stage
					)
				)
			),
			[
				this
			]()
			{
				return
					fcppt::make_cref(
						*defaults_
					);
			}
		).get();
}

void
sge::opengl::state::core::sampler::context::reset()
{
	objects_.clear();
}

sge::opengl::context::id const
sge::opengl::state::core::sampler::context::static_id(
	sge::opengl::context::make_id()
);
