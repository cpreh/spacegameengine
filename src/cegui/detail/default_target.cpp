#include "../declare_local_logger.hpp"
#include <CEGUI/CEGUIGeometryBuffer.h>
#include <CEGUI/CEGUIRenderQueue.h>
#include <sge/cegui/detail/default_target.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>
#include <iostream>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("default_target"))

// cegui's internal OpenGL renderer uses a static viewport (I
// think). The area is initialized to the current viewport in the
// constructor and is changed only by setArea which is called by the
// renderer after a window size change. 

// sge already provides this viewport-adaption technique so I just
// update the viewport variable when the viewport is requested.
sge::cegui::detail::default_target::default_target(
	sge::renderer::device_ptr const _renderer)
:
	renderer_(
		_renderer),
	viewport_()
{
}

void 
sge::cegui::detail::default_target::draw(
	CEGUI::GeometryBuffer const &buffer)
{
	buffer.draw();
}

void 
sge::cegui::detail::default_target::draw(
	CEGUI::RenderQueue const &queue)
{
	queue.draw();
}

void 
sge::cegui::detail::default_target::setArea(
	CEGUI::Rect const &r)
{
	// This is a check to see if setArea might be called from outside,
	// too. If this fails, it _should_ indicate that indeed, it _is_
	// called from outside the renderer
	FCPPT_ASSERT(
		structure_cast<sge::renderer::pixel_rect>(r) == renderer_->onscreen_target()->viewport().get());
}

CEGUI::Rect const &
sge::cegui::detail::default_target::getArea() const
{
	viewport_ =
		structure_cast(
			renderer_->target()->viewport().get());
	return viewport_;
}

bool 
sge::cegui::detail::default_target::isImageryCache() const
{
	return false;
}

void 
sge::cegui::detail::default_target::activate()
{
}

void 
sge::cegui::detail::default_target::deactivate()
{
}

void 
sge::cegui::detail::default_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2 const & p_in, 
	CEGUI::Vector2& p_out) const
{
	FCPPT_ASSERT_MESSAGE(
		false,
		FCPPT_TEXT("default_target::unprojectPoint not implemented yet"));
	p_out = p_in;
}

sge::renderer::matrix4 const
sge::cegui::detail::default_target::projection() const
{
	return 
		fcppt::math::matrix::orthogonal(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				renderer_->onscreen_target()->viewport().get().size().w()),
			static_cast<sge::renderer::scalar>(
				renderer_->onscreen_target()->viewport().get().size().h()),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				2));
}
