/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/core.hpp>
#include <sge/d3d9/system.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/system_unique_ptr.hpp>
#include <sge/renderer/caps/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::d3d9::core::core()
:
	sge::renderer::core()
{
}

sge::d3d9::core::~core()
{
}

sge::renderer::system_unique_ptr
sge::d3d9::core::create_system(
	awl::system::object &
)
{
	return
		fcppt::make_unique_ptr<
			sge::d3d9::system
		>();
}

sge::renderer::caps::system_field const
sge::d3d9::core::caps() const
{
	return
		sge::renderer::caps::system_field{
			sge::renderer::caps::system::ffp
		};
}
