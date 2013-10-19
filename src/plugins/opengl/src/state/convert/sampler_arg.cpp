/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/state/convert/sampler_arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::sampler_arg(
	sge::renderer::state::ffp::sampler::arg const _value
)
{
	switch(
		_value
	)
	{
	case sge::renderer::state::ffp::sampler::arg::previous:
		return GL_PREVIOUS;
	case sge::renderer::state::ffp::sampler::arg::texture:
		return GL_TEXTURE;
	case sge::renderer::state::ffp::sampler::arg::constant:
		return GL_CONSTANT;
	// TODO: Which extensions do we have to check here?
	case sge::renderer::state::ffp::sampler::arg::vertex_color:
		return GL_PRIMARY_COLOR;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
