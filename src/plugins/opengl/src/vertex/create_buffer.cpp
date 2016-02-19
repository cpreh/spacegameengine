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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/create_buffer.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


sge::renderer::vertex::buffer_unique_ptr
sge::opengl::vertex::create_buffer(
	sge::opengl::context::object &_context,
	sge::renderer::vertex::buffer_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::vertex::buffer
		>(
			fcppt::make_unique_ptr<
				sge::opengl::vertex::buffer
			>(
				_context,
				_parameters.part(),
				fcppt::cast::static_downcast<
					sge::opengl::vertex::declaration const &
				>(
					_parameters.declaration()
				).format_part(
					_parameters.part()
				),
				_parameters.count(),
				_parameters.flags()
			)
		);
}
