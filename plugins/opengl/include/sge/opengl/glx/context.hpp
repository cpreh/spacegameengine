//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_GLX_CONTEXT_HPP_INCLUDED

#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/glx/context_fwd.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

class context
:
	public sge::opengl::backend::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context(
		fcppt::log::object &,
		awl::backends::x11::window::base &,
		sge::opengl::glx::optional_proc_address_function
	);

	~context()
	override;
private:
	sge::opengl::backend::current_unique_ptr
	activate()
	override;

	void
	deactivate(
		sge::opengl::backend::current_unique_ptr &&
	)
	override;

	fcppt::log::object &log_;

	awl::backends::x11::window::base &window_;

	sge::opengl::glx::optional_proc_address_function const proc_address_;

	GLXContext const context_;
};

}
}
}

#endif
