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


#ifndef SGE_OPENGL_WINDOWS_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{

class system
:
	public sge::opengl::platform::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system();

	~system()
	override;
private:
	sge::renderer::caps::device_count
	device_count() const
	override;

	sge::renderer::display_mode::container
	display_modes(
		sge::renderer::device::index
	) const
	override;

	sge::opengl::platform::device_state_unique_ptr
	create_device_state(
		sge::renderer::display_mode::optional_object const &,
		awl::window::object &,
		awl::window::event::processor &
	)
	override;
};

}
}
}

#endif
