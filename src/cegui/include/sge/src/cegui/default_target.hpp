/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_CEGUI_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_SRC_CEGUI_DEFAULT_TARGET_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/fwds/vector2f_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/RenderTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
}

namespace sge
{
namespace cegui
{

class default_target
:
	public CEGUI::RenderTarget
{
	FCPPT_NONCOPYABLE(
		default_target
	);
public:
	default_target(
		sge::renderer::device::ffp &,
		sge::cegui::optional_render_context_ref const &
	);

	~default_target()
	override;
private:
	void
	draw(
		CEGUI::GeometryBuffer const &
	)
	override;

	void
	draw(
		CEGUI::RenderQueue const &
	)
	override;
public:
	void
	setArea(
		CEGUI::Rectf const &
	)
	override;
private:
	CEGUI::Rectf const &
	getArea() const
	override;

	bool
	isImageryCache() const
	override;

	void
	activate()
	override;

	void
	deactivate()
	override;

	void
	unprojectPoint(
		CEGUI::GeometryBuffer const &,
		CEGUI::Vector2f const &p_in,
		CEGUI::Vector2f &p_out
	) const
	override;

	sge::renderer::device::ffp &renderer_;

	CEGUI::Rectf viewport_;

	sge::renderer::state::ffp::transform::optional_object_unique_ptr transform_;

	sge::cegui::optional_render_context_ref const &render_context_;
};

}
}

#endif
