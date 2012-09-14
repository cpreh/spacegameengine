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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/ffp/clip_plane/make_actors.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/core/value.hpp>
#include <boost/phoenix/bind/bind_function.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::index_actor const
sge::opengl::state::ffp::clip_plane::make_actors(
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	typedef fcppt::math::vector::static_<
		GLdouble,
		4
	>::type vector4d;

	return
		sge::opengl::state::wrap_error_handler(
			boost::phoenix::bind(
				::glClipPlane,
				boost::phoenix::arg_names::arg1,
				boost::phoenix::bind(
					static_cast<
						vector4d::const_pointer
						(vector4d::*)() const
					>(
						&vector4d::data
					),
					boost::phoenix::val(
						fcppt::math::vector::structure_cast<
							vector4d
						>(
							_parameters.area().get()
						)
					)
				)
			),
			FCPPT_TEXT("glClipPlane")
		);
}
