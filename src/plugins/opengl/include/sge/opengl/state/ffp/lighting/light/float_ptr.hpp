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


#ifndef SGE_OPENGL_STATE_FFP_LIGHTING_LIGHT_FLOAT_PTR_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_LIGHTING_LIGHT_FLOAT_PTR_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <fcppt/text.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace light
{

template<
	typename Vector
>
sge::opengl::state::index_actor
float_ptr(
	GLenum const _name,
	Vector const &_vector
)
{
	return
		sge::opengl::state::wrap_error_handler<
			sge::opengl::state::index_actor
		>(
			[
				_name,
				_vector
			](
				GLenum const _index
			)
			{
				::glLightfv(
					_index,
					_name,
					_vector.data()
				);
			},
			FCPPT_TEXT("glLightfv")
		);
}

}
}
}
}
}
}

#endif
