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


#ifndef SGE_SRC_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_SRC_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <sge/src/cegui/batch.hpp>
#include <sge/src/cegui/geometry_buffer_fwd.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUIBase.h>
#include <CEGUIGeometryBuffer.h>
#include <CEGUITexture.h>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class RenderEffect;
class Rect;
struct Vertex;
class Vector3;
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
		sge::renderer::device &,
		sge::renderer::vertex_declaration const &
	);

	~geometry_buffer();

	void
	render_context(
		sge::cegui::optional_render_context_ref const &
	);
private:
	void
	draw() const;

	void
	setTranslation(
		CEGUI::Vector3 const &
	);

	void
	setRotation(
		CEGUI::Vector3 const &
	);

	void
	setPivot(
		CEGUI::Vector3 const &
	);

	void
	setClippingRegion(
		CEGUI::Rect const &
	);

	void
	appendVertex(
		CEGUI::Vertex const &
	);

	void
	appendGeometry(
		CEGUI::Vertex const *const, // const for VC++
		CEGUI::uint vertex_count
	);

	void
	setActiveTexture(
		CEGUI::Texture *
	);

	void
	reset();

	CEGUI::Texture*
	getActiveTexture() const;

	CEGUI::uint
	getVertexCount() const;

	CEGUI::uint
	getBatchCount() const;

	void
	setRenderEffect(
		CEGUI::RenderEffect *
	);

	CEGUI::RenderEffect *
	getRenderEffect();

	void
	setBlendMode(
		CEGUI::BlendMode const
	); // const for VC++

	CEGUI::BlendMode
	getBlendMode() const;
private:
	typedef
	std::vector
	<
		sge::cegui::batch
	>
	batch_sequence;

	batch_sequence batches_;

	sge::renderer::device &renderer_;

	sge::renderer::vertex_declaration const &vertex_declaration_;

	// This is important only to cegui, so this is CEGUI::uint instead
	// of renderer::size_type
	CEGUI::uint total_vertex_count_;

	sge::cegui::texture *active_texture_;

	CEGUI::BlendMode blend_mode_;

	sge::renderer::vector3 translation_;

	sge::renderer::vector3 rotation_pivot_;

	sge::renderer::vector3 rotation_axis_;

	sge::renderer::target::scissor_area scissor_area_;

	sge::cegui::optional_render_context_ref render_context_;
};

}
}

#endif
