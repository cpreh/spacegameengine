/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_SRC_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/src/cegui/batch.hpp>
#include <sge/src/cegui/clip.hpp>
#include <sge/src/cegui/geometry_buffer_fwd.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/fwds/rectf_fwd.hpp>
#include <sge/src/cegui/fwds/vector3f_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/GeometryBuffer.h>
#include <boost/math/quaternion.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class Quaternion;
class RenderEffect;
struct Vertex;
class Texture;
}

namespace sge
{
namespace cegui
{

class geometry_buffer
:
	public CEGUI::GeometryBuffer
{
	FCPPT_NONCOPYABLE(
		geometry_buffer
	);
public:
	geometry_buffer(
		sge::renderer::device::ffp &,
		sge::renderer::vertex::declaration const &,
		sge::cegui::optional_render_context_ref const &
	);

	~geometry_buffer()
	override;
private:
	void
	draw() const
	override;

	void
	setTranslation(
		CEGUI::Vector3f const &
	)
	override;

	void
	setRotation(
		CEGUI::Quaternion const &
	)
	override;

	void
	setPivot(
		CEGUI::Vector3f const &
	)
	override;

	void
	setClippingRegion(
		CEGUI::Rectf const &
	)
	override;

	void
	appendVertex(
		CEGUI::Vertex const &
	)
	override;

	void
	appendGeometry(
		CEGUI::Vertex const *,
		CEGUI::uint vertex_count
	)
	override;

	void
	setActiveTexture(
		CEGUI::Texture *
	)
	override;

	void
	reset()
	override;

	CEGUI::Texture *
	getActiveTexture() const
	override;

	CEGUI::uint
	getVertexCount() const
	override;

	CEGUI::uint
	getBatchCount() const
	override;

	void
	setRenderEffect(
		CEGUI::RenderEffect *
	)
	override;

	CEGUI::RenderEffect *
	getRenderEffect()
	override;

	void
	setClippingActive(
		bool
	)
	override;

	bool
	isClippingActive() const
	override;
private:
	typedef
	std::vector<
		sge::cegui::batch
	>
	batch_sequence;

	typedef
	boost::math::quaternion<
		sge::renderer::scalar
	>
	quaternion;

	batch_sequence batches_;

	sge::renderer::device::ffp &renderer_;

	sge::renderer::vertex::declaration const &vertex_declaration_;

	sge::cegui::texture *active_texture_;

	sge::renderer::vector3 translation_;

	sge::renderer::vector3 pivot_;

	quaternion rotation_;

	sge::renderer::target::scissor_area scissor_area_;

	sge::cegui::optional_render_context_ref const &render_context_;

	sge::cegui::clip clip_;

	CEGUI::RenderEffect *render_effect_;

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_on_;

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_off_;
};

}
}

#endif
