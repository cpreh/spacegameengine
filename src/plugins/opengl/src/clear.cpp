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


#include "../clear.hpp"
#include "../check_state.hpp"
#include "../common.hpp"
#include "../convert/clear_flags.hpp"
#include <sge/renderer/clear_flags.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/text.hpp>

namespace
{

GLenum
clear_bit(
	sge::renderer::clear_flags_field const &_field,
	sge::renderer::clear_flags::type const _value
)
{
	return
		_field[
			_value
		]
		?
			sge::opengl::convert::clear_flags(
				_value
			)
		:
			0;
}


}

void
sge::opengl::clear(
	sge::renderer::clear_flags_field const &_flags
)
{
	::glClear(
		::clear_bit(
			_flags,
			renderer::clear_flags::back_buffer
		)
		|
		::clear_bit(
			_flags,
			renderer::clear_flags::depth_buffer
		)
		|
		::clear_bit(
			_flags,
			renderer::clear_flags::stencil_buffer
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glClear failed"),
		sge::renderer::exception
	)
}
