/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/cegui/structure_cast.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/color_surface_shared_ptr.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/target/offscreen.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <sge/src/cegui/texture.hpp>
#include <sge/src/cegui/texture_target.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIGeometryBuffer.h>
#include <CEGUIRenderQueue.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("texture_target"))

sge::cegui::texture_target::texture_target(
	sge::cegui::texture_parameters const &_texture_parameters,
	sge::renderer::matrix4 const &_projection
)
:
	texture_parameters_(
		_texture_parameters
	),
	target_(
		texture_parameters_.renderer().create_target()
	),
	texture_(),
	render_context_(),
	// This is exactly what cegui does and it avoids certain bugs :/
	area_(0,0,0,0),
	default_projection_(
		_projection
	)
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::texture_target"));
}

sge::cegui::texture_target::~texture_target()
{
}

void
sge::cegui::texture_target::draw(
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
sge::cegui::texture_target::draw(
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
sge::cegui::texture_target::setArea(
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
sge::cegui::texture_target::getArea() const
{
	return area_;
}

bool
sge::cegui::texture_target::isImageryCache() const
{
	return true;
}

void
sge::cegui::texture_target::activate()
{
	if(texture_->empty())
		return;

	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::activate()"));

	target_->viewport(
		sge::renderer::target::viewport(
			structure_cast<sge::renderer::pixel_rect>(
				area_)));
	if(
		!render_context_
	)
		render_context_.take(
			fcppt::make_unique_ptr<
				sge::renderer::context::scoped
			>(
				fcppt::ref(
					texture_parameters_.renderer()
				),
				fcppt::ref(
					*target_
				)
			)
		);

	render_context_->get().transform(
		sge::renderer::matrix_mode::projection,
		sge::renderer::projection::orthogonal(
			sge::cegui::structure_cast<
				sge::renderer::projection::rect
			>(
				area_
			),
			sge::renderer::projection::near(
				0.f
			),
			sge::renderer::projection::far(
				2.f
			)
		)
	);
}

void
sge::cegui::texture_target::deactivate()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("texture_target(")
			<< this
			<< FCPPT_TEXT(")::deactivate()")
	);

	if(
		texture_->empty()
	)
		return;

	render_context_->get().transform(
		sge::renderer::matrix_mode::projection,
		default_projection_
	);

	render_context_.reset();
}

void
sge::cegui::texture_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2 const &,
	CEGUI::Vector2 &
) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("texture_target::unprojectPoint not implemented yet")
	);
}

void
sge::cegui::texture_target::clear()
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ << FCPPT_TEXT("texture_target(") << this << FCPPT_TEXT(")::clear()"));

	if (texture_->empty())
		return;

	if(
		!render_context_
	)
		render_context_.take(
			fcppt::make_unique_ptr<
				sge::renderer::context::scoped
			>(
				fcppt::ref(
					texture_parameters_.renderer()
				),
				fcppt::ref(
					*target_
				)
			)
		);

	sge::renderer::state::scoped const scoped_state(
		render_context_->get(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::enable_scissor_test = false)
	);

	// Make sure we clear everything
	target_->viewport(
		sge::renderer::target::viewport(
			sge::renderer::pixel_rect(
				sge::renderer::pixel_rect::vector::null(),
				fcppt::math::dim::structure_cast<sge::renderer::pixel_rect::dim>(
					texture_->impl().size()))));

	render_context_->get().clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::colors::transparent()
		)
	);
}

CEGUI::Texture &
sge::cegui::texture_target::getTexture() const
{
	return *texture_;
}

void
sge::cegui::texture_target::declareRenderSize(
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
		fcppt::make_unique_ptr<
			sge::cegui::texture
		>(
			fcppt::ref(
				texture_parameters_
			),
			sge::renderer::texture::capabilities_field(
				sge::renderer::texture::capabilities::render_target)));

	texture_->resize(
		_size);

	target_->color_surface(
	// The size here could be (0,0), for example if the viewport hasn't
	// been initialized yet. If that's the case, we shouldn't switch
		texture_->empty()
		?
			sge::renderer::color_surface_shared_ptr()
		:
			sge::renderer::color_surface_shared_ptr(
				texture_->impl().surface(
					sge::renderer::texture::mipmap::level(
						0u
					)
				)
			)
		,
		sge::renderer::target::surface_index(0u)
	);

	this->clear();
}

bool
sge::cegui::texture_target::isRenderingInverted() const
{
	return true;
}
