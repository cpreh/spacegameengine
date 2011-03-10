#ifndef SGE_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_CEGUI_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/cegui/texture_fwd.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <CEGUI/CEGUIGeometryBuffer.h>
#include <CEGUI/CEGUIVector.h>
#include <CEGUI/CEGUIVertex.h>
#include <CEGUI/CEGUITexture.h>
#include <CEGUI/CEGUIBase.h>
#include <CEGUI/CEGUIRect.h>
#include <CEGUI/CEGUIRenderEffect.h>
#include <sge/renderer/vertex_buffer_ptr.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/scissor_area.hpp>
#include <sge/renderer/vertex_declaration_ptr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL geometry_buffer
:
	public CEGUI::GeometryBuffer
{
FCPPT_NONCOPYABLE(
	geometry_buffer);
public:
	SGE_CEGUI_SYMBOL explicit
	geometry_buffer(
		sge::renderer::device_ptr,
		sge::renderer::vertex_declaration_ptr);

	SGE_CEGUI_SYMBOL void 
	draw() const;

	SGE_CEGUI_SYMBOL void 
	setTranslation(
		CEGUI::Vector3 const & v);

	SGE_CEGUI_SYMBOL void 
	setRotation(
		CEGUI::Vector3 const &);

	SGE_CEGUI_SYMBOL void 
	setPivot(
		CEGUI::Vector3 const &);

	SGE_CEGUI_SYMBOL void 
	setClippingRegion(
		CEGUI::Rect const &);

	SGE_CEGUI_SYMBOL void 
	appendVertex(
		CEGUI::Vertex const &);

	SGE_CEGUI_SYMBOL void 
	appendGeometry(
		CEGUI::Vertex const *,
		CEGUI::uint vertex_count);

	SGE_CEGUI_SYMBOL void 
	setActiveTexture(
		CEGUI::Texture*);

	SGE_CEGUI_SYMBOL void 
	reset();

	SGE_CEGUI_SYMBOL CEGUI::Texture* 
	getActiveTexture() const;

	SGE_CEGUI_SYMBOL CEGUI::uint 
	getVertexCount() const;

	SGE_CEGUI_SYMBOL CEGUI::uint 
	getBatchCount() const;

	SGE_CEGUI_SYMBOL void 
	setRenderEffect(
		CEGUI::RenderEffect*);

	SGE_CEGUI_SYMBOL CEGUI::RenderEffect* 
	getRenderEffect();

	SGE_CEGUI_SYMBOL void 
	setBlendMode(
		CEGUI::BlendMode);

	SGE_CEGUI_SYMBOL CEGUI::BlendMode 
	getBlendMode() const;

	SGE_CEGUI_SYMBOL ~geometry_buffer();
private:
	struct batch
	{
		sge::renderer::texture::planar_ptr texture_;
		sge::renderer::vertex_buffer_ptr vb_;

		// Yes, this should be placed in a separate header, TODO
		explicit
		batch(
			sge::renderer::texture::planar_ptr const _texture,
			sge::renderer::vertex_buffer_ptr const _vb)
		:
			texture_(
				_texture),
			vb_(
				_vb)
		{
		}
	};

	typedef
	std::vector<batch>
	batch_sequence;

	batch_sequence batches_;
	sge::renderer::device_ptr renderer_;
	sge::renderer::vertex_declaration_ptr vertex_declaration_;
	// This is important only to cegui, so this is CEGUI::uint instead
	// of renderer::size_type
	CEGUI::uint total_vertex_count_;
	texture *active_texture_;
	CEGUI::BlendMode blend_mode_;
	sge::renderer::vector3 translation_;
	sge::renderer::vector3 rotation_pivot_;
	sge::renderer::vector3 rotation_axis_;
	sge::renderer::scissor_area scissor_area_;
};
}
}

#endif
