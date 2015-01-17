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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/set_or_default_single.hpp>
#include <sge/opengl/state/ffp/misc/default_context.hpp>
#include <sge/opengl/state/ffp/misc/object.hpp>
#include <sge/opengl/state/ffp/misc/set.hpp>
#include <sge/renderer/state/ffp/misc/const_optional_object_ref.hpp>


void
sge::opengl::state::ffp::misc::set(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::state::ffp::misc::const_optional_object_ref const &_state
)
{
	sge::opengl::state::set_or_default_single<
		sge::opengl::state::ffp::misc::object
	>(
		sge::opengl::context::use<
			sge::opengl::state::ffp::misc::default_context
		>(
			_system_context,
			_system_context
		),
		_state
	);
}
