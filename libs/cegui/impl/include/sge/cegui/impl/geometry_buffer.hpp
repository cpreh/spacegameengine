//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_CEGUI_IMPL_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/cegui/impl/batch.hpp>
#include <sge/cegui/impl/clip.hpp>
#include <sge/cegui/impl/geometry_buffer_fwd.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture_fwd.hpp>
#include <sge/cegui/impl/fwds/rectf_fwd.hpp>
#include <sge/cegui/impl/fwds/vector3f_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/core/rasterizer/object_unique_ptr.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Quaternion.h>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class RenderEffect;
struct Vertex;
class Texture;
}

namespace sge
{
namespace cegui
{
namespace impl
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
		fcppt::log::object &,
		sge::renderer::device::ffp &,
		sge::renderer::vertex::declaration const &,
		sge::cegui::impl::optional_render_context_ref const &
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
	mutable fcppt::log::object log_;

	typedef
	std::vector<
		sge::cegui::impl::batch
	>
	batch_sequence;

	batch_sequence batches_;

	sge::renderer::device::ffp &renderer_;

	sge::renderer::vertex::declaration const &vertex_declaration_;

	typedef
	fcppt::optional::reference<
		sge::cegui::impl::texture
	>
	optional_texture_ref;

	optional_texture_ref active_texture_;

	sge::renderer::vector3 translation_;

	sge::renderer::vector3 pivot_;

	CEGUI::Quaternion rotation_;

	sge::renderer::target::scissor_area scissor_area_;

	sge::cegui::impl::optional_render_context_ref const &render_context_;

	sge::cegui::impl::clip clip_;

	typedef
	fcppt::optional::reference<
		CEGUI::RenderEffect
	>
	optional_render_effect_ref;

	optional_render_effect_ref render_effect_;

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_on_;

	sge::renderer::state::core::rasterizer::object_unique_ptr const rasterizer_scissor_off_;
};

}
}
}

#endif
