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


#include <sge/cegui/structure_cast.hpp>
#include <sge/cegui/detail/default_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/src/cegui/declare_local_logger.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIGeometryBuffer.h>
#include <CEGUIRenderQueue.h>
#include <fcppt/config/external_end.hpp>


SGE_CEGUI_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("default_target"))

// cegui's internal OpenGL renderer uses a static viewport (I
// think). The area is initialized to the current viewport in the
// constructor and is changed only by setArea which is called by the
// renderer after a window size change.

// sge already provides this viewport-adaption technique so I just
// update the viewport variable when the viewport is requested.
sge::cegui::detail::default_target::default_target(
	sge::renderer::device &_renderer)
:
	renderer_(
		_renderer),
	viewport_()
{
}

sge::cegui::detail::default_target::~default_target()
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
	FCPPT_ASSERT_ERROR(
		structure_cast<sge::renderer::pixel_rect>(r) == renderer_.onscreen_target().viewport().get());
}

CEGUI::Rect const &
sge::cegui::detail::default_target::getArea() const
{
	viewport_ =
		structure_cast(
			renderer_.target()->viewport().get());
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
	renderer_.transform(
		sge::renderer::matrix_mode::projection,
		projection());
}

void
sge::cegui::detail::default_target::deactivate()
{
}

void
sge::cegui::detail::default_target::unprojectPoint(
	CEGUI::GeometryBuffer const &,
	CEGUI::Vector2 const &,
	CEGUI::Vector2 &) const
{
	FCPPT_ASSERT_UNIMPLEMENTED_MESSAGE(
		FCPPT_TEXT("default_target::unprojectPoint not implemented yet"));
}

sge::renderer::matrix4 const
sge::cegui::detail::default_target::projection() const
{
	return
		sge::renderer::projection::orthogonal(
			sge::renderer::projection::rect(
				sge::renderer::projection::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::projection::rect::dim
				>(
					sge::renderer::viewport_size(
						renderer_
					)
				)
			),
			sge::renderer::projection::near(
				0
			),
			sge::renderer::projection::far(
				2
			)
		);
}
