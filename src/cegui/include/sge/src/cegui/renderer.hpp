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


#ifndef SGE_SRC_CEGUI_RENDERER_HPP_INCLUDED
#define SGE_SRC_CEGUI_RENDERER_HPP_INCLUDED

#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/vertex/declaration_scoped_ptr.hpp>
#include <sge/src/cegui/default_target.hpp>
#include <sge/src/cegui/geometry_buffer_fwd.hpp>
#include <sge/src/cegui/optional_render_context_ref.hpp>
#include <sge/src/cegui/texture_fwd.hpp>
#include <sge/src/cegui/texture_parameters.hpp>
#include <sge/src/cegui/texture_target_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/Renderer.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Vector.h>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace CEGUI
{
class GeometryBuffer;
class RenderTarget;
class Texture;
class TextureTarget;
}

namespace sge
{
namespace cegui
{

class renderer
:
	public CEGUI::Renderer
{
	FCPPT_NONCOPYABLE(
		renderer
	);
public:
	explicit
	renderer(
		sge::cegui::texture_parameters const &
	);

	~renderer();

	void
	render_context(
		sge::cegui::optional_render_context_ref const &
	);

	sge::renderer::device::ffp &
	impl() const;

	CEGUI::RenderTarget &
	getDefaultRenderTarget();
private:
	CEGUI::GeometryBuffer &
	createGeometryBuffer();

	void
	destroyGeometryBuffer(
		CEGUI::GeometryBuffer const &
	);

	void
	destroyAllGeometryBuffers();

	CEGUI::TextureTarget *
	createTextureTarget();

	void
	destroyTextureTarget(
		CEGUI::TextureTarget *
	);

	void
	destroyAllTextureTargets();

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name
	);

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name,
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup
	);

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name,
		CEGUI::Sizef const &
	);

	void
	destroyTexture(
		CEGUI::Texture &
	);

	void
	destroyTexture(
		CEGUI::String const &name
	);

	void
	destroyAllTextures();

	CEGUI::Texture &
	getTexture(
		CEGUI::String const &
	) const;

	bool
	isTextureDefined(
		CEGUI::String const &
	) const;

	void
	beginRendering();

	void
	endRendering();

	void
	setDisplaySize(
		CEGUI::Sizef const &
	);

	CEGUI::Sizef const &
	getDisplaySize() const;

	CEGUI::Vector2f const &
	getDisplayDPI() const;

	CEGUI::uint
	getMaxTextureSize() const;

	CEGUI::String const &
	getIdentifierString() const;

	typedef std::unique_ptr<
		sge::cegui::texture
	> texture_unique_ptr;

	CEGUI::Texture &
	insert_texture(
		CEGUI::String const &name,
		sge::cegui::renderer::texture_unique_ptr
	);

	typedef
	boost::ptr_vector<
		sge::cegui::geometry_buffer
	> geometry_buffer_sequence;

	typedef
	boost::ptr_vector<
		sge::cegui::texture_target
	> texture_target_sequence;

	typedef
	boost::ptr_map<
		CEGUI::String,
		sge::cegui::texture
	> texture_map;

	sge::cegui::texture_parameters const texture_parameters_;

	sge::renderer::device::ffp &renderer_;

	sge::cegui::optional_render_context_ref render_context_;

	sge::renderer::vertex::declaration_scoped_ptr const vertex_declaration_;

	CEGUI::Sizef display_size_;

	CEGUI::Vector2f display_dpi_;

	CEGUI::String const identifier_;

	sge::cegui::default_target default_target_;

	geometry_buffer_sequence geometry_buffers_;

	texture_target_sequence texture_targets_;

	texture_map textures_;
};

}
}

#endif
