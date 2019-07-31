//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/opengl/backend/current_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/target/basic.hpp>
#include <sge/opengl/target/onscreen_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace target
{

class onscreen
:
	public
		sge::opengl::target::basic<
			sge::renderer::target::onscreen
		>
{
	FCPPT_NONCOPYABLE(
		onscreen
	);
public:
	typedef
	sge::opengl::target::basic<
		sge::renderer::target::onscreen
	>
	base;

	onscreen(
		sge::opengl::context::object &,
		sge::opengl::backend::current &,
		awl::window::object &
	);

	~onscreen()
	override;
private:
	void
	on_bind()
	override;

	void
	on_unbind()
	override;

	void
	end_rendering()
	override;

	sge::renderer::color_buffer::readable_surface const &
	surface() const
	override;

	sge::renderer::screen_unit
	height() const
	override;

	typedef
	fcppt::unique_ptr<
		sge::renderer::color_buffer::readable_surface
	>
	color_surface_unique_ptr;

	sge::opengl::backend::current &current_;

	color_surface_unique_ptr const main_surface_;
};

}
}
}

#endif
