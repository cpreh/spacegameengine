#include "../declare_local_logger.hpp"
#include <sge/cegui/detail/texture_target.hpp>
#include <sge/cegui/system.hpp>
#include <sge/cegui/detail/texture.hpp>
#include <sge/cegui/structure_cast.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/state/color.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/scoped_target.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/default_target.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/image/colors.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <iostream>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture_target"))

sge::cegui::detail::texture_target::texture_target(
	system &_system)
:
	system_(
		_system),
	target_(
		system_.renderer()->create_target()),
	texture_(),
	// This is exactly what cegui does and it avoids certain bugs :/
	area_(0,0,0,0),
	temp_projection_()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::texture_target"));
}
	
void 
sge::cegui::detail::texture_target::draw(
	CEGUI::GeometryBuffer const &buffer)
{
	// Disabled for debugging reasons
	//if(texture_->empty())
	//	return;
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::draw(GeometryBuffer)"));
	buffer.draw();
}

void 
sge::cegui::detail::texture_target::draw(
	CEGUI::RenderQueue const & queue)
{
	// Disabled for debugging reasons
	//if(texture_->empty())
	//	return;
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::draw(RenderQueue)"));
	queue.draw();
}

void 
sge::cegui::detail::texture_target::setArea(
	CEGUI::Rect const &_area)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::setArea(" 
			<< structure_cast<sge::renderer::pixel_rect>(_area) << ")"));
	area_ = 
		_area;
}

CEGUI::Rect const &
sge::cegui::detail::texture_target::getArea() const
{
	return area_;
}

bool 
sge::cegui::detail::texture_target::isImageryCache() const
{
	return true;
}

void 
sge::cegui::detail::texture_target::activate()
{
	if(texture_->empty())
		return;

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::activate()"));

	target_->viewport(
		sge::renderer::viewport(
			structure_cast<sge::renderer::pixel_rect>(
				area_)));

	system_.renderer()->target(
		target_);

	temp_projection_ = 
		system_.renderer()->transform(
			sge::renderer::matrix_mode::projection);

	system_.renderer()->transform(
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::orthogonal(
			static_cast<sge::renderer::scalar>(
				area_.getPosition().d_x),
			static_cast<sge::renderer::scalar>(
				area_.getWidth()),
			// Note that technically, we flip everything here
			static_cast<sge::renderer::scalar>(
				area_.getHeight()),
			static_cast<sge::renderer::scalar>(
				area_.getPosition().d_y),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				2)));

	// This is critical: We do NOT want to clear the texture
	// here. Clearing is explicitly done in the clear() function.
	system_.renderer()->push_state(
		sge::renderer::state::list(
			sge::renderer::state::bool_::clear_backbuffer = false));

	system_.renderer()->begin_rendering();
}

void 
sge::cegui::detail::texture_target::deactivate()
{
	if(texture_->empty())
		return;
	system_.renderer()->end_rendering();
	system_.renderer()->pop_state();
	system_.renderer()->transform(
		sge::renderer::matrix_mode::projection,
		temp_projection_);
	system_.renderer()->target(
		sge::renderer::default_target());
}

void 
sge::cegui::detail::texture_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2 const &, 
	CEGUI::Vector2 &) const
{
	FCPPT_ASSERT_MESSAGE(
		false,
		FCPPT_TEXT("texture_target::unprojectPoint not implemented yet"));
}

void 
sge::cegui::detail::texture_target::clear()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::clear()"));
	if (texture_->empty())
		return;

	sge::renderer::state::scoped scoped_state(
		system_.renderer(),
		sge::renderer::state::list
			(sge::renderer::state::color::clear_color = sge::image::colors::transparent())
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::enable_scissor_test = false));

	// Make sure we clear everything
	target_->viewport(
		sge::renderer::viewport(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
					texture_->impl()->dim()))));

	sge::renderer::scoped_target scoped_target(
		system_.renderer(),
		target_);

	sge::renderer::scoped_block scoped_block(
		system_.renderer());
}

CEGUI::Texture &
sge::cegui::detail::texture_target::getTexture() const
{
	return *texture_;
}

void 
sge::cegui::detail::texture_target::declareRenderSize(
	CEGUI::Size const &_size)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::declareRenderSize(") 
			<< structure_cast<sge::renderer::dim2>(_size) << FCPPT_TEXT(")"));

	setArea(
		CEGUI::Rect(
			area_.getPosition(),
			_size));

	texture_.take(
		fcppt::make_unique_ptr<texture>(
			std::tr1::ref(
				system_),
			sge::renderer::texture::capabilities::render_target));

	texture_->resize(
		_size);

	target_->color_surface(
	// The size here could be (0,0), for example if the viewport hasn't
	// been initialized yet. If that's the case, we shouldn't switch 
		texture_->empty()
		?
			sge::renderer::color_surface_ptr()
		:
			texture_->impl()->surface(
				sge::renderer::stage_type(0u)),
		sge::renderer::surface_index(0u));

	clear();
}

bool 
sge::cegui::detail::texture_target::isRenderingInverted() const
{
	return true;
}

sge::cegui::detail::texture_target::~texture_target()
{
}
