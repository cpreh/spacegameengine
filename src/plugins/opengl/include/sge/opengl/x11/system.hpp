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


#ifndef SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/xrandr/system_fwd.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/device/index.hpp>
#include <awl/backends/x11/system/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class system
:
	public sge::opengl::platform::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		awl::backends::x11::system::object &
	);

	~system()
	override;
private:
	sge::renderer::caps::device_count const
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

	typedef
	fcppt::scoped_ptr<
		sge::opengl::xrandr::system
	>
	xrandr_scoped_ptr;

	xrandr_scoped_ptr const xrandr_system_;
};

}
}
}

#endif
