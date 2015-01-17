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


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/enable_bool.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/off_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::ffp::lighting::visitor::result_type
sge::opengl::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::off const &
) const
{
	return
		sge::opengl::state::ffp::lighting::visitor::result_type{
			std::bind(
				sge::opengl::disable,
				GL_LIGHTING
			)
		};
}

sge::opengl::state::ffp::lighting::visitor::result_type
sge::opengl::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::enabled const &_enabled
) const
{
	sge::image::color::rgba32f const ambient{
		sge::image::color::any::convert<
			sge::image::color::rgba32f_format
		>(
			_enabled.ambient_color().get()
		)
	};

	return
		sge::opengl::state::ffp::lighting::visitor::result_type{
			std::bind(
				sge::opengl::enable,
				GL_LIGHTING
			),
			sge::opengl::state::wrap_error_handler<
				sge::opengl::state::actor
			>(
				[
					ambient
				]
				{
					::glLightModelfv(
						GL_LIGHT_MODEL_AMBIENT,
						ambient.data()
					);
				},
				FCPPT_TEXT("glLightModelfv")
			),
			std::bind(
				sge::opengl::enable_bool,
				GL_COLOR_MATERIAL,
				_enabled.diffuse_from_vertex().get()
			)
		};
}
