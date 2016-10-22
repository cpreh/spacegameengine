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


#include <sge/image/color/element_count.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_to_format_type.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/color_actor.hpp>
#include <sge/opengl/vf/convert_color_format.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::vf::color_actor::color_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::color const &_color
)
:
	sge::opengl::vf::fp_actor(
		_param,
		GL_COLOR_ARRAY
	),
	elements_(
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				sge::image::color::element_count(
					_color.color_format()
				)
			)
		)
	),
	format_(
		sge::opengl::convert::color_to_format_type(
			sge::opengl::vf::convert_color_format(
				_color.color_format()
			)
		)
	)
{
}

sge::opengl::vf::color_actor::~color_actor()
{
}

void
sge::opengl::vf::color_actor::on_use(
	sge::opengl::vf::pointer const _src
) const
{
	sge::opengl::call(
		::glColorPointer,
		elements_,
		format_.get(),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				this->stride().get()
			)
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glColorPointer failed"),
		sge::renderer::exception
	)
}
