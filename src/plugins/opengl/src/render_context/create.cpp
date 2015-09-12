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


#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/render_context/create.hpp>
#include <sge/opengl/render_context/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/ffp_unique_ptr.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::context::ffp_unique_ptr
sge::opengl::render_context::create(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::target::base &_target
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::context::ffp
		>(
			fcppt::make_unique_ptr<
				sge::opengl::render_context::object
			>(
				_system_context,
				_device_context,
				_target
			)
		);
}
