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


#ifndef SGE_OPENGL_X11_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_X11_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/xrandr/optional_system_ref_fwd.hpp>
#include <sge/opengl/xrandr/resolution_fwd.hpp>
#include <sge/opengl/xrandr/state_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class device_state
:
	public sge::opengl::platform::device_state
{
	FCPPT_NONCOPYABLE(
		device_state
	);
public:
	device_state(
		fcppt::log::object &,
		sge::opengl::xrandr::optional_system_ref const &,
		sge::renderer::display_mode::optional_object const &,
		awl::backends::x11::window::object &
	);

	~device_state()
	override;
private:
	sge::renderer::display_mode::optional_object
	display_mode() const
	override;

	void
	display_mode(
		sge::renderer::display_mode::optional_object const &
	)
	override;

	typedef
	fcppt::unique_ptr<
		sge::opengl::xrandr::state
	>
	xrandr_state_unique_ptr;

	typedef
	fcppt::optional::object<
		xrandr_state_unique_ptr
	>
	optional_xrandr_state_unique_ptr;

	typedef
	fcppt::unique_ptr<
		sge::opengl::xrandr::resolution
	>
	resolution_unique_ptr;

	typedef
	fcppt::optional::object<
		resolution_unique_ptr
	>
	optional_resolution_unique_ptr;

	fcppt::log::object &log_;

	optional_xrandr_state_unique_ptr const xrandr_state_;

	optional_resolution_unique_ptr resolution_;
};

}
}
}

#endif
