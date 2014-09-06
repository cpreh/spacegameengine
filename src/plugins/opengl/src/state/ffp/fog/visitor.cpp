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


#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/fog_mode.hpp>
#include <sge/opengl/state/ffp/fog/color.hpp>
#include <sge/opengl/state/ffp/fog/float.hpp>
#include <sge/opengl/state/ffp/fog/visitor.hpp>
#include <sge/renderer/state/ffp/fog/enabled.hpp>
#include <sge/renderer/state/ffp/fog/off_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::ffp::fog::visitor::result_type
sge::opengl::state::ffp::fog::visitor::operator()(
	sge::renderer::state::ffp::fog::off const &
) const
{
	return
		sge::opengl::state::ffp::fog::visitor::result_type{
			std::bind(
				sge::opengl::disable,
				GL_FOG
			)
		};
}

sge::opengl::state::ffp::fog::visitor::result_type
sge::opengl::state::ffp::fog::visitor::operator()(
	sge::renderer::state::ffp::fog::enabled const &_enabled
) const
{
	return
		sge::opengl::state::ffp::fog::visitor::result_type{
			std::bind(
				sge::opengl::enable,
				GL_FOG
			),
			sge::opengl::state::wrap_error_handler<
				sge::opengl::state::actor
			>(
				std::bind(
					::glFogi,
					GL_FOG_MODE,
					sge::opengl::state::convert::fog_mode(
						_enabled.mode()
					)
				),
				FCPPT_TEXT("glFogi")
			),
			sge::opengl::state::ffp::fog::float_(
				GL_FOG_START,
				_enabled.start().get()
			),
			sge::opengl::state::ffp::fog::float_(
				GL_FOG_END,
				_enabled.end().get()
			),
			sge::opengl::state::ffp::fog::float_(
				GL_FOG_DENSITY,
				_enabled.density().get()
			),
			sge::opengl::state::ffp::fog::color(
				_enabled.color()
			)
		};
}
