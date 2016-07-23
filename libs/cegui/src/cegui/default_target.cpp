/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/log/default_parameters.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/pixel_rect.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/src/cegui/default_target.hpp>
#include <sge/src/cegui/from_cegui_rect.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/to_cegui_rect.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/assert/unimplemented_message.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
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
	fcppt::log::object &_log,
	sge::renderer::device::ffp &_renderer,
	sge::cegui::optional_render_context_ref const &_render_context
)
:
	log_{
		_log,
		sge::log::default_parameters(
			fcppt::log::name{
				FCPPT_TEXT("default_target")
			}
		)
	},
	renderer_(
		_renderer
	),
	viewport_(),
	transform_(),
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
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("default_target(")
			<< this
			<< FCPPT_TEXT(")::draw(GeometryBuffer)")
	);

	_buffer.draw();
}

void
sge::cegui::default_target::draw(
	CEGUI::RenderQueue const &_queue
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("default_target(")
			<< this
			<< FCPPT_TEXT(")::draw(RenderQueue)")
	);

	_queue.draw();
}

void
sge::cegui::default_target::setArea(
	CEGUI::Rectf const &_area
)
{
	CEGUI::RenderTargetEventArgs args(
		this
	);

	viewport_ = _area;

	transform_ =
		fcppt::optional::map(
			sge::renderer::projection::orthogonal_viewport(
				sge::renderer::target::viewport(
					sge::cegui::from_cegui_rect<
						sge::renderer::pixel_rect
					>(
						viewport_
					)
				),
				sge::renderer::projection::near(
					0.f
				),
				sge::renderer::projection::far(
					10.f
				)
			),
			[
				this
			](
				sge::renderer::matrix4 const &_matrix
			)
			{
				return
					renderer_.create_transform_state(
						sge::renderer::state::ffp::transform::parameters(
							_matrix
						)
					);
			}
		);

	this->fireEvent(
		CEGUI::RenderTarget::EventAreaChanged,
		args
	);
}

CEGUI::Rectf const &
sge::cegui::default_target::getArea() const
{
	return
		viewport_;
}

bool
sge::cegui::default_target::isImageryCache() const
{
	return
		false;
}

void
sge::cegui::default_target::activate()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("default_target(")
			<< this
			<< FCPPT_TEXT(")::activate()")
	);

	fcppt::optional::maybe_void(
		transform_,
		[
			this
		](
			sge::renderer::state::ffp::transform::object_unique_ptr const &_transform
		)
		{
			FCPPT_ASSERT_OPTIONAL_ERROR(
				render_context_
			).get().transform(
				sge::renderer::state::ffp::transform::mode::projection,
				sge::renderer::state::ffp::transform::const_optional_object_ref(
					fcppt::make_cref(
						*_transform
					)
				)
			);
		}
	);
}

void
sge::cegui::default_target::deactivate()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("default_target(")
			<< this
			<< FCPPT_TEXT(")::deactivate()")
	);

	FCPPT_ASSERT_OPTIONAL_ERROR(
		render_context_
	).get().transform(
		sge::renderer::state::ffp::transform::mode::projection,
		sge::renderer::state::ffp::transform::const_optional_object_ref()
	);
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
