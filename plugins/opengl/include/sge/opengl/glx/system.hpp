//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_GLX_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/optional_proc_address_function.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/x11/system/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

class system
:
	public sge::opengl::backend::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		fcppt::log::object &,
		awl::backends::x11::system::object &
	);

	~system()
	override;
private:
	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	sge::opengl::backend::context_unique_ptr
	create_context(
		sge::window::object &
	)
	override;

	fcppt::log::object &log_;

	awl::backends::x11::system::object &awl_system_;

	sge::opengl::glx::optional_proc_address_function const get_proc_address_;

	sge::opengl::glx::extension_set const extensions_;

	sge::opengl::glx::visual::optional_srgb_flag const srgb_flag_;
};

}
}
}

#endif
