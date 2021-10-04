//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_EGL_SYSTEM_HPP_INCLUDED

#include <sge/opengl/backend/context_unique_ptr.hpp>
#include <sge/opengl/backend/system.hpp>
#include <sge/opengl/egl/display_unique_ptr.hpp>
#include <sge/opengl/egl/init.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/system/object_ref.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl
{

class system
:
	public sge::opengl::backend::system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	system(
		fcppt::log::object_reference,
		awl::system::object_ref
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
		sge::window::object_ref
	)
	override;

	fcppt::log::object_reference const log_;

	awl::system::object_ref const awl_system_;

	sge::opengl::egl::display_unique_ptr const egl_display_;

	sge::opengl::egl::init const init_;
};

}

#endif
