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


#include <sge/opengl/core.hpp>
#include <sge/opengl/system.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::core::core()
:
	sge::renderer::core()
{
}

sge::opengl::core::~core()
{
}

sge::renderer::system_unique_ptr
sge::opengl::core::create_system(
	awl::system::object &_awl_system
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::system
		>(
			fcppt::make_unique_ptr<
				sge::opengl::system
			>(
				_awl_system
			)
		);
}

sge::renderer::caps::system_field
sge::opengl::core::caps() const
{
	return
		sge::renderer::caps::system_field{
			sge::renderer::caps::system::opengl,
			sge::renderer::caps::system::ffp
		};
}
