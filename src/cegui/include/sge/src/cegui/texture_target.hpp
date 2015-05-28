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


#ifndef SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_SRC_CEGUI_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/state/ffp/transform/optional_object_unique_ptr.hpp>
#include <sge/renderer/target/offscreen_unique_ptr.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/texture_target_fwd.hpp>
#include <sge/src/cegui/fwds/sizef_fwd.hpp>
#include <sge/src/cegui/fwds/vector2f_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <CEGUI/TextureTarget.h>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Texture;
}

namespace sge
{
namespace cegui
{

class texture_target
:
	public CEGUI::TextureTarget
{
	FCPPT_NONCOPYABLE(
		texture_target
	);
public:
	texture_target(
		sge::cegui::texture_parameters const &,
		sge::cegui::optional_render_context_ref const &
	);

	~texture_target()
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

	void
	setArea(
		CEGUI::Rectf const &
	)
	override;

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
		CEGUI::GeometryBuffer const & buff,
		CEGUI::Vector2f const &p_in,
		CEGUI::Vector2f & p_out
	) const
	override;

	void
	clear()
	override;

	CEGUI::Texture &
	getTexture() const
	override;

	void
	declareRenderSize(
		CEGUI::Sizef const &
	)
	override;

	bool
	isRenderingInverted() const
	override;
private:
	sge::cegui::texture_parameters const texture_parameters_;

	typedef
	fcppt::unique_ptr<
		sge::cegui::texture
	>
	texture_unique_ptr;

	typedef
	fcppt::optional<
		texture_unique_ptr
	>
	optional_texture_unique_ptr;

	sge::renderer::target::offscreen_unique_ptr const target_;

	sge::cegui::optional_render_context_ref const &render_context_;

	optional_texture_unique_ptr texture_;

	CEGUI::Rectf area_;

	sge::renderer::caps::render_target_inverted const is_inverted_;

	sge::renderer::state::ffp::transform::optional_object_unique_ptr transform_state_;
};

}
}

#endif
