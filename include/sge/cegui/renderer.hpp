#ifndef SGE_CEGUI_RENDERER_HPP_INCLUDED
#define SGE_CEGUI_RENDERER_HPP_INCLUDED

#include <sge/cegui/default_target.hpp>
#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/geometry_buffer.hpp>
#include <sge/cegui/texture_target.hpp>
#include <sge/cegui/texture.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <sge/class_symbol.hpp>
#include <CEGUI/CEGUIBase.h>
#include <CEGUI/CEGUIRenderer.h>
#include <CEGUI/CEGUIString.h>
#include <CEGUI/CEGUIRenderingRoot.h>
#include <fcppt/noncopyable.hpp> 
#include <fcppt/signal/scoped_connection.hpp> 
#include <fcppt/math/matrix/basic_impl.hpp> 
#include <fcppt/container/array.hpp> 
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL renderer
:
	public CEGUI::Renderer
{
FCPPT_NONCOPYABLE(
	renderer);
public:
	SGE_CEGUI_SYMBOL explicit
	renderer(
		system &,
		sge::renderer::device_ptr);

	SGE_CEGUI_SYMBOL CEGUI::RenderingRoot &
	getDefaultRenderingRoot();

	SGE_CEGUI_SYMBOL CEGUI::GeometryBuffer &
	createGeometryBuffer();

	SGE_CEGUI_SYMBOL void 
	destroyGeometryBuffer(
		CEGUI::GeometryBuffer const &);

	SGE_CEGUI_SYMBOL void 
	destroyAllGeometryBuffers();

	SGE_CEGUI_SYMBOL CEGUI::TextureTarget * 
	createTextureTarget();

	SGE_CEGUI_SYMBOL void 
	destroyTextureTarget(
		CEGUI::TextureTarget *);

	SGE_CEGUI_SYMBOL void 
	destroyAllTextureTargets();

	SGE_CEGUI_SYMBOL CEGUI::Texture & 
	createTexture();

	SGE_CEGUI_SYMBOL CEGUI::Texture &
	createTexture(
		CEGUI::String const &filename,
		CEGUI::String const &resourceGroup);

	SGE_CEGUI_SYMBOL CEGUI::Texture &
	createTexture(
		CEGUI::Size const &);

	SGE_CEGUI_SYMBOL void 
	destroyTexture(
		CEGUI::Texture &);

	SGE_CEGUI_SYMBOL void 
	destroyAllTextures();

	SGE_CEGUI_SYMBOL void 
	beginRendering();

	SGE_CEGUI_SYMBOL void 
	endRendering();

	SGE_CEGUI_SYMBOL void 
	setDisplaySize(
		CEGUI::Size const &);

	SGE_CEGUI_SYMBOL CEGUI::Size const &
	getDisplaySize() const;

	SGE_CEGUI_SYMBOL CEGUI::Vector2 const &
	getDisplayDPI() const;

	SGE_CEGUI_SYMBOL CEGUI::uint 
	getMaxTextureSize() const;

	SGE_CEGUI_SYMBOL CEGUI::String const & 
	getIdentifierString() const;

	SGE_CEGUI_SYMBOL sge::renderer::device_ptr const
	impl() const;

 	SGE_CEGUI_SYMBOL ~renderer();
private:
	typedef
	boost::ptr_vector<geometry_buffer>
	geometry_buffer_sequence;

	typedef
	boost::ptr_vector<texture_target>
	texture_target_sequence;

	typedef
	boost::ptr_vector<texture>
	texture_sequence;

	system &system_;
	sge::renderer::device_ptr renderer_;
	sge::renderer::vertex_declaration_ptr vertex_declaration_;
	CEGUI::Size display_size_;
	CEGUI::Vector2 display_dpi_;
	CEGUI::String const identifier_;
	default_target default_target_;
	CEGUI::RenderingRoot default_root_;
	geometry_buffer_sequence geometry_buffers_;
	texture_target_sequence texture_targets_;
	texture_sequence textures_;
	fcppt::signal::scoped_connection viewport_change_connection_;

	typedef
	fcppt::container::array<sge::renderer::matrix4,3>
	transform_array;

	transform_array transforms_;
};
}
}

#endif
