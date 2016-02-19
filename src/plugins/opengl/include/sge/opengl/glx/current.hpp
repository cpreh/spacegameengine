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


#ifndef SGE_OPENGL_GLX_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_GLX_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

class current
:
	public sge::opengl::backend::current
{
	FCPPT_NONCOPYABLE(
		current
	);
public:
	current(
		awl::backends::x11::window::object &,
		sge::opengl::glx::optional_proc_address_function const &
	);

	~current()
	override;
private:
	sge::opengl::backend::fun_ptr
	load_function(
		std::string const &
	) const
	override;

	void
	begin_rendering()
	override;

	void
	end_rendering()
	override;

	void
	vsync(
		sge::renderer::display_mode::vsync
	)
	override;

	awl::backends::x11::window::object &window_;

	sge::opengl::glx::optional_proc_address_function const proc_address_;

	typedef
	fcppt::optional::object<
		sge::opengl::glx::swap_functions
	>
	optional_swap_functions;

	optional_swap_functions const swap_functions_;
};

}
}
}

#endif
