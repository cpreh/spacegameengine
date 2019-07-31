//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_RENDERER_HPP_INCLUDED
#define SGE_CEGUI_IMPL_RENDERER_HPP_INCLUDED

#include <sge/cegui/impl/default_target.hpp>
#include <sge/cegui/impl/geometry_buffer_fwd.hpp>
#include <sge/cegui/impl/optional_render_context_ref.hpp>
#include <sge/cegui/impl/texture_fwd.hpp>
#include <sge/cegui/impl/texture_parameters.hpp>
#include <sge/cegui/impl/texture_target_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/Renderer.h>
#include <CEGUI/Size.h>
#include <CEGUI/String.h>
#include <CEGUI/Vector.h>
#include <map>
#include <vector>
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
namespace impl
{

class renderer
:
	public CEGUI::Renderer
{
	FCPPT_NONCOPYABLE(
		renderer
	);
public:
	renderer(
		fcppt::log::object &,
		sge::cegui::impl::texture_parameters const &
	);

	~renderer()
	override;

	void
	render_context(
		sge::cegui::impl::optional_render_context_ref const &
	);

	sge::renderer::device::ffp &
	impl() const;

	CEGUI::RenderTarget &
	getDefaultRenderTarget()
	override;
private:
	CEGUI::GeometryBuffer &
	createGeometryBuffer()
	override;

	void
	destroyGeometryBuffer(
		CEGUI::GeometryBuffer const &
	)
	override;

	void
	destroyAllGeometryBuffers()
	override;

	CEGUI::TextureTarget *
	createTextureTarget()
	override;

	void
	destroyTextureTarget(
		CEGUI::TextureTarget *
	)
	override;

	void
	destroyAllTextureTargets()
	override;

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name
	)
	override;

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name,
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup
	)
	override;

	CEGUI::Texture &
	createTexture(
		CEGUI::String const &name,
		CEGUI::Sizef const &
	)
	override;

	void
	destroyTexture(
		CEGUI::Texture &
	)
	override;

	void
	destroyTexture(
		CEGUI::String const &name
	)
	override;

	void
	destroyAllTextures()
	override;

	CEGUI::Texture &
	getTexture(
		CEGUI::String const &
	) const
	override;

	bool
	isTextureDefined(
		CEGUI::String const &
	) const
	override;

	void
	beginRendering()
	override;

	void
	endRendering()
	override;

	void
	setDisplaySize(
		CEGUI::Sizef const &
	)
	override;

	CEGUI::Sizef const &
	getDisplaySize() const
	override;

	CEGUI::Vector2f const &
	getDisplayDPI() const
	override;

	CEGUI::uint
	getMaxTextureSize() const
	override;

	CEGUI::String const &
	getIdentifierString() const
	override;

	typedef
	fcppt::unique_ptr<
		sge::cegui::impl::texture
	>
	texture_unique_ptr;

	CEGUI::Texture &
	insert_texture(
		CEGUI::String const &name,
		sge::cegui::impl::renderer::texture_unique_ptr
	);

	typedef
	fcppt::unique_ptr<
		sge::cegui::impl::geometry_buffer
	>
	geometry_buffer_unique_ptr;

	typedef
	std::vector<
		geometry_buffer_unique_ptr
	>
	geometry_buffer_sequence;

	typedef
	fcppt::unique_ptr<
		sge::cegui::impl::texture_target
	>
	texture_target_unique_ptr;

	typedef
	std::vector<
		texture_target_unique_ptr
	>
	texture_target_sequence;

	typedef
	std::map<
		CEGUI::String,
		texture_unique_ptr
	>
	texture_map;

	fcppt::log::object &main_log_;

	fcppt::log::object log_;

	sge::cegui::impl::texture_parameters const texture_parameters_;

	sge::renderer::device::ffp &renderer_;

	sge::cegui::impl::optional_render_context_ref render_context_;

	sge::renderer::vertex::declaration_unique_ptr const vertex_declaration_;

	CEGUI::Sizef display_size_;

	CEGUI::Vector2f display_dpi_;

	CEGUI::String const identifier_;

	sge::cegui::impl::default_target default_target_;

	geometry_buffer_sequence geometry_buffers_;

	texture_target_sequence texture_targets_;

	texture_map textures_;
};

}
}
}

#endif
