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


#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/src/cegui/default_target.hpp>
#include <sge/src/cegui/from_cegui_rect.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/to_cegui_rect.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderQueue.h>
#include <CEGUI/RenderTarget.h>
#include <fcppt/config/external_end.hpp>


// cegui's internal OpenGL renderer uses a static viewport (I
// think). The area is initialized to the current viewport in the
// constructor and is changed only by setArea which is called by the
// renderer after a window size change.

// sge already provides this viewport-adaption technique so I just
// update the viewport variable when the viewport is requested.
sge::cegui::default_target::default_target(
	sge::renderer::device &_renderer,
	sge::cegui::optional_render_context_ref const &_render_context
)
:
	renderer_(
		_renderer
	),
	viewport_(),
	render_context_(
		_render_context
	)
{
}

sge::cegui::default_target::~default_target()
{
}

void
sge::cegui::default_target::draw(
	CEGUI::GeometryBuffer const &_buffer
)
{
	_buffer.draw();
}

void
sge::cegui::default_target::draw(
	CEGUI::RenderQueue const &_queue
)
{
	_queue.draw();
}

void
sge::cegui::default_target::setArea(
	CEGUI::Rectf const &_area
)
{
	// This is a check to see if setArea might be called from outside,
	// too. If this fails, it _should_ indicate that indeed, it _is_
	// called from outside the renderer
	FCPPT_ASSERT_ERROR(
		sge::cegui::from_cegui_rect<
			sge::renderer::pixel_rect
		>(
			_area
		)
		==
		renderer_.onscreen_target().viewport().get()
	);

	CEGUI::RenderTargetEventArgs args(
		this
	);

	this->fireEvent(
		CEGUI::RenderTarget::EventAreaChanged,
		args
	);
}

CEGUI::Rectf const &
sge::cegui::default_target::getArea() const
{
	viewport_ =
		sge::cegui::to_cegui_rect<
			CEGUI::Rectf::value_type
		>(
			renderer_.onscreen_target().viewport().get()
		);

	return
		viewport_;
}

bool
sge::cegui::default_target::isImageryCache() const
{
	return false;
}

void
sge::cegui::default_target::activate()
{
	FCPPT_ASSERT_PRE(
		render_context_
	);

	render_context_->transform(
		sge::renderer::matrix_mode::projection,
		this->projection()
	);
}

void
sge::cegui::default_target::deactivate()
{
}

void
sge::cegui::default_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2f const &,
	CEGUI::Vector2f &
) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("default_target::unprojectPoint not implemented yet")
	);
}

sge::renderer::matrix4 const
sge::cegui::default_target::projection() const
{
	return
		sge::renderer::projection::orthogonal(
			sge::renderer::projection::rect(
				sge::renderer::projection::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::projection::rect::dim
				>(
					sge::renderer::target::viewport_size(
						renderer_.onscreen_target()
					)
				)
			),
			sge::renderer::projection::near(
				0.f
			),
			sge::renderer::projection::far(
				2.f
			)
		);
}
