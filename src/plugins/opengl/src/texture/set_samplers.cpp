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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>


void
sge::opengl::texture::set_samplers(
	sge::opengl::texture::render_binding const &_render_binding,
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context
)
{
	sge::opengl::context::use<
		sge::opengl::state::core::sampler::context
	>(
		_device_context,
		_system_context
	).get(
		_render_binding.stage()
	).set(
		_render_binding
	);
}
