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
#include <sge/opengl/state/ffp/misc/default_context_parameters.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::state::ffp::misc::default_context_parameters::default_context_parameters(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context
)
:
	log_{
		_log
	},
	context_{
		_context
	}
{
}

fcppt::log::object &
sge::opengl::state::ffp::misc::default_context_parameters::log() const
{
	return
		log_;
}

sge::opengl::context::object &
sge::opengl::state::ffp::misc::default_context_parameters::context() const
{
	return
		context_;
}
