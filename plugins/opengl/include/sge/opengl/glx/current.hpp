//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_CURRENT_HPP_INCLUDED
#define SGE_OPENGL_GLX_CURRENT_HPP_INCLUDED

#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/opengl/glx/swap_functions.hpp>
#include <sge/renderer/display_mode/vsync_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
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
		fcppt::log::object &,
		awl::backends::x11::window::base &,
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

	fcppt::log::object &log_;

	awl::backends::x11::window::base &window_;

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
