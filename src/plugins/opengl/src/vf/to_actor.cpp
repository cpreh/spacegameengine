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


#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/actor_ptr.hpp>
#include <sge/opengl/vf/to_actor.hpp>
#include <sge/opengl/vf/to_actor_visitor.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/variant/apply_unary.hpp>


sge::opengl::vf::actor_ptr
sge::opengl::vf::to_actor(
	sge::renderer::vf::dynamic::ordered_element const &_element,
	sge::renderer::vf::dynamic::stride const _stride,
	sge::opengl::context::system::object &_system_context
)
{
	return
		fcppt::variant::apply_unary(
			sge::opengl::vf::to_actor_visitor(
				sge::opengl::vf::actor_parameters(
					_stride,
					_element.offset(),
					_system_context
				)
			),
			_element.element().info()
		);
}
