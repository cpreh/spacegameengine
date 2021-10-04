//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_OPENGL_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/opengl/backend/current_ref.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/target/basic.hpp>
#include <sge/opengl/target/onscreen_fwd.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <awl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge::opengl::target
{

class onscreen
:
	public
		sge::opengl::target::basic<
			sge::renderer::target::onscreen
		>
{
	FCPPT_NONMOVABLE(
		onscreen
	);
public:
	using
	base
	=
	sge::opengl::target::basic<
		sge::renderer::target::onscreen
	>;

	onscreen(
		sge::opengl::context::object_ref,
		sge::opengl::backend::current_ref,
		awl::window::object_ref
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

	[[nodiscard]]
	sge::renderer::color_buffer::readable_surface const &
	surface() const
	override;

	[[nodiscard]]
	sge::renderer::screen_unit
	height() const
	override;

	using
	color_surface_unique_ptr
	=
	fcppt::unique_ptr<
		sge::renderer::color_buffer::readable_surface
	>;

	sge::opengl::backend::current_ref const current_;

	color_surface_unique_ptr const main_surface_;
};

}

#endif
