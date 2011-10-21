/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../color_actor.hpp"
#include "../../convert/color_to_format_type.hpp"
#include "../../check_state.hpp"
#include <sge/image/color/element_count.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <fcppt/text.hpp>


sge::opengl::vf::color_actor::color_actor(
	actor_parameters const &_param,
	sge::renderer::vf::dynamic::color const & _color
)
:
	fp_actor(
		_param,
		GL_COLOR_ARRAY
	),
	elements_(
		static_cast<
			GLint
		>(
			sge::image::color::element_count(
				_color.color_format()
			)
		)
	),
	format_(
		opengl::convert::color_to_format_type(
			_color.color_format()
		)
	)
{
}

sge::opengl::vf::color_actor::~color_actor()
{
}

void
sge::opengl::vf::color_actor::on_use(
	vf::pointer const _src
) const
{
	::glColorPointer(
		elements_,
		format_.get(),
		static_cast<
			GLsizei
		>(
			stride()
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glColorPointer failed"),
		sge::renderer::exception
	)
}
