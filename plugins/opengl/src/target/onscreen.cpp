//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/target/basic_impl.hpp>
#include <sge/opengl/target/onscreen.hpp>
#include <sge/opengl/target/onscreen_surface.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/color_buffer/readable_surface.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::target::onscreen::onscreen(
	sge::opengl::context::object &_context,
	sge::opengl::backend::current &_current,
	awl::window::object &_window
)
:
	base(
		_context,
		sge::renderer::target::viewport(
			fcppt::math::box::null<
				sge::renderer::pixel_rect
			>()
		)
	),
	current_(
		_current
	),
	main_surface_(
		fcppt::unique_ptr_to_base<
			sge::renderer::color_buffer::readable_surface
		>(
			fcppt::make_unique_ptr<
				sge::opengl::target::onscreen_surface
			>(
				_window
			)
		)
	)
{
}

sge::opengl::target::onscreen::~onscreen()
{
}

void
sge::opengl::target::onscreen::on_bind()
{
}

void
sge::opengl::target::onscreen::on_unbind()
{
}

void
sge::opengl::target::onscreen::end_rendering()
{
	current_.end_rendering();
}

sge::renderer::color_buffer::readable_surface const &
sge::opengl::target::onscreen::surface() const
{
	return
		*main_surface_;
}

sge::renderer::screen_unit
sge::opengl::target::onscreen::height() const
{
	return
		fcppt::cast::size<
			sge::renderer::screen_unit
		>(
			main_surface_->size().h()
		);
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wweak-template-vtables)

template
class
sge::opengl::target::basic<
	sge::renderer::target::onscreen
>;

FCPPT_PP_POP_WARNING
