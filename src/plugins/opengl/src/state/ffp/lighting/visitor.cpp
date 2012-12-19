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


#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba32f_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/bind_data_getter.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/lighting/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/enabled.hpp>
#include <sge/renderer/state/ffp/lighting/off_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::ffp::lighting::visitor::result_type const
sge::opengl::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::off const &
) const
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::ffp::lighting::visitor::result_type
		>(
			std::bind(
				sge::opengl::disable,
				GL_LIGHTING
			)
		);
}

sge::opengl::state::ffp::lighting::visitor::result_type const
sge::opengl::state::ffp::lighting::visitor::operator()(
	sge::renderer::state::ffp::lighting::enabled const &_enabled
) const
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::ffp::lighting::visitor::result_type
		>(
			std::bind(
				sge::opengl::enable,
				GL_LIGHTING
			)
		)(
			sge::opengl::state::wrap_error_handler<
				sge::opengl::state::actor
			>(
				boost::phoenix::bind(
					::glLightModelfv,
					GL_LIGHT_MODEL_AMBIENT,
					boost::phoenix::bind(
						sge::opengl::state::bind_data_getter(
							sge::image::color::any::convert<
								sge::image::color::rgba32f_format
							>(
								_enabled.ambient_color().get()
							)
						)
					)
				),
				FCPPT_TEXT("glLightModelfv")
			)
		);
}
