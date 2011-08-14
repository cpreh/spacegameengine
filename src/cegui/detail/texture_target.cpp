/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/stage.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/default_target.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/image/colors.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>

SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture_target"))

sge::cegui::detail::texture_target::texture_target(
	system &_system)
:
	system_(
		_system),
	target_(
		system_.renderer().create_target()),
	texture_(),
	// This is exactly what cegui does and it avoids certain bugs :/
	area_(0,0,0,0),
	default_projection_(
		system_.renderer_.default_target_.projection())
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

	system_.renderer().target(
		target_.get());

	system_.renderer().transform(
		sge::renderer::matrix_mode::projection,
		sge::renderer::projection::orthogonal(
			sge::cegui::structure_cast<
				sge::renderer::projection::rect
			>(
				area_
			),
			sge::renderer::projection::near(
				0
			),
			sge::renderer::projection::far(
				2
			)
		)
	);

	// This is critical: We do NOT want to clear the texture
	// here. Clearing is explicitly done in the clear() function.
	system_.renderer().push_state(
		sge::renderer::state::list(
			sge::renderer::state::bool_::clear_back_buffer = false));

	system_.renderer().begin_rendering();
}

void
sge::cegui::detail::texture_target::deactivate()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::deactivate()"));
	if(texture_->empty())
		return;
	system_.renderer().end_rendering();
	system_.renderer().pop_state();
	system_.renderer().transform(
		sge::renderer::matrix_mode::projection,
		default_projection_);
	system_.renderer().target(
		sge::renderer::default_target());
}

void
sge::cegui::detail::texture_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2 const &,
	CEGUI::Vector2 &) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
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
			(sge::renderer::state::color::back_buffer_clear_color = sge::image::colors::transparent())
			(sge::renderer::state::bool_::clear_back_buffer = true)
			(sge::renderer::state::bool_::enable_scissor_test = false));

	// Make sure we clear everything
	target_->viewport(
		sge::renderer::viewport(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
					texture_->impl().size()))));

	sge::renderer::scoped_target scoped_target(
		system_.renderer(),
		*target_);

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
			fcppt::ref(
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
			texture_->impl().surface(
				sge::renderer::stage(0u)),
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
