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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/transform/default_context.hpp>
#include <sge/opengl/state/ffp/transform/object.hpp>
#include <sge/opengl/state/ffp/transform/set.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::state::ffp::transform::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &_object
)
{
	fcppt::optional::maybe(
		_object,
		[
			&_context
		]()
		{
			return
				fcppt::make_cref(
					sge::opengl::context::use<
						sge::opengl::state::ffp::transform::default_context
					>(
						_context,
						_context
					).default_state()
				);
		},
		[](
			fcppt::reference<
				sge::renderer::state::ffp::transform::object const
			> const _transform
		)
		{
			return
				fcppt::make_cref(
					fcppt::cast::static_downcast<
						sge::opengl::state::ffp::transform::object const &
					>(
						_transform.get()
					)
				);
		}
	).get().set(
		_mode
	);
}
