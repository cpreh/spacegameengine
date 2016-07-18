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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/state/ffp/misc/default_context.hpp>
#include <sge/opengl/state/ffp/misc/make_actors.hpp>
#include <sge/opengl/state/ffp/misc/object.hpp>
#include <sge/renderer/state/ffp/misc/default.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>


sge::opengl::state::ffp::misc::default_context::default_context(
	sge::opengl::state::ffp::misc::default_context::parameter const _parameter
)
:
	sge::opengl::context::base(),
	default_state_(
		fcppt::make_unique_ptr<
			sge::opengl::state::ffp::misc::object
		>(
			sge::opengl::state::ffp::misc::make_actors(
				_parameter.first.get(),
				_parameter.second.get(),
				sge::renderer::state::ffp::misc::default_()
			)
		)
	)
{
}

sge::opengl::state::ffp::misc::default_context::~default_context()
{
}

sge::opengl::state::ffp::misc::object const &
sge::opengl::state::ffp::misc::default_context::default_state() const
{
	return
		*default_state_;
}

sge::opengl::context::id const
sge::opengl::state::ffp::misc::default_context::static_id(
	sge::opengl::context::make_id()
);
