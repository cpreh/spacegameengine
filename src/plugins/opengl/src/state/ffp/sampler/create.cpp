/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/state/ffp/sampler/create.hpp>
#include <sge/opengl/state/ffp/sampler/make_actors.hpp>
#include <sge/opengl/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::renderer::state::ffp::sampler::object_unique_ptr
sge::opengl::state::ffp::sampler::create(
	sge::renderer::state::ffp::sampler::parameters const &_parameters
)
{
	return
		sge::renderer::state::ffp::sampler::object_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::state::ffp::sampler::object
			>(
				sge::opengl::state::ffp::sampler::make_actors(
					_parameters
				)
			)
		);
}
