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


#ifndef SGE_OPENGL_XRANDR_STATE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_STATE_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <sge/opengl/xrandr/resolution_fwd.hpp>
#include <sge/opengl/xrandr/state_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <awl/backends/x11/window/event/object_fwd.hpp>
#include <awl/backends/x11/window/event/processor_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		sge::opengl::xrandr::extension const &,
		awl::backends::x11::window::object &,
		awl::backends::x11::window::event::processor &,
		sge::renderer::display_mode::optional_object const &
	);

	~state();

	sge::renderer::display_mode::optional_object const
	display_mode() const;
private:
	void
	change_callback(
		awl::backends::x11::window::event::object const &
	);

	void
	configure_callback(
		awl::backends::x11::window::event::object const &
	);

	void
	update();

	awl::backends::x11::display &display_;

	awl::backends::x11::window::object &window_;

	sge::opengl::xrandr::configuration const config_;

	typedef
	fcppt::scoped_ptr<
		sge::opengl::xrandr::resolution
	>
	resolution_scoped_ptr;

	resolution_scoped_ptr const resolution_;

	sge::renderer::display_mode::optional_object display_mode_;

	fcppt::signal::scoped_connection const change_connection_;

	fcppt::signal::scoped_connection const configure_connection_;
};

}
}
}

#endif
