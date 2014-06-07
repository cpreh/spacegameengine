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


#ifndef SGE_OPENGL_STATE_SET_ARRAY_HPP_INCLUDED
#define SGE_OPENGL_STATE_SET_ARRAY_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/renderer/state/index_count.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename GLState,
	typename Context,
	typename States,
	typename ConvertFunction
>
void
set_array(
	Context &_context,
	States const &_states,
	ConvertFunction const &_convert_function
)
{
	sge::renderer::state::index_count const count(
		static_cast<
			sge::renderer::state::index_count
		>(
			_states.size()
		)
	);

	for(
		sge::renderer::state::index_count index(
			0u
		);
		index < count;
		++index
	)
	{
		GLenum const gl_index(
			_convert_function(
				index
			)
		);

		sge::opengl::enable(
			gl_index
		);

		static_cast<
			GLState const &
		>(
			_states[
				index
			].get()
		).set(
			gl_index
		);
	}

	for(
		sge::renderer::state::index_count index(
			count
		);
		index < _context.indices();
		++index
	)
		sge::opengl::disable(
			_convert_function(
				index
			)
		);

	_context.indices(
		count
	);
}

}
}
}

#endif
