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


#ifndef SGE_OPENGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_SYSTEM_HPP_INCLUDED

#include <sge/renderer/adapter.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/system.hpp>
#include <sge/window/instance_ptr.hpp>
#include <sge/window/simple_parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{

class system
:
	public renderer::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system();

	renderer::device_ptr const
	create_renderer(
		renderer::parameters const &,
		renderer::adapter,
		window::instance &
	);

	awl::window::instance_shared_ptr const
	create_window(
		awl::system::object &,
		sge::window::simple_parameters const &,
		sge::renderer::parameters const &
	);
};

}
}

#endif
