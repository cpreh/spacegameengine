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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/convert/sampler_binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::state::convert::sampler_binary_op(
	sge::renderer::state::ffp::sampler::binary_op_type const _op
)
{
	switch(
		_op
	)
	{
	case sge::renderer::state::ffp::sampler::binary_op_type::modulate:
		return GL_MODULATE;
	case sge::renderer::state::ffp::sampler::binary_op_type::add:
		return GL_ADD;
	case sge::renderer::state::ffp::sampler::binary_op_type::subtract:
		return GL_SUBTRACT;
	case sge::renderer::state::ffp::sampler::binary_op_type::add_signed:
		return GL_ADD_SIGNED;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
