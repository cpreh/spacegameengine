#ifndef SGE_CEGUI_DETAIL_GEOMETRY_BUFFER_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_GEOMETRY_BUFFER_HPP_INCLUDED

#include <sge/cegui/detail/texture_fwd.hpp>
#include <CEGUI/CEGUIGeometryBuffer.h>
#include <CEGUI/CEGUITexture.h>
#include <CEGUI/CEGUIBase.h>
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

namespace CEGUI
{
class RenderEffect;
class Rect;
class Vertex;
class Vector3;
class Texture;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class geometry_buffer
:
	public CEGUI::GeometryBuffer
{
FCPPT_NONCOPYABLE(
	geometry_buffer);
public:
	explicit
	geometry_buffer(
		sge::renderer::device_ptr,
		sge::renderer::vertex_declaration_ptr);

	void 
	draw() const;

	void 
	setTranslation(
		CEGUI::Vector3 const & v);

	void 
	setRotation(
		CEGUI::Vector3 const &);

	void 
	setPivot(
		CEGUI::Vector3 const &);

	void 
	setClippingRegion(
		CEGUI::Rect const &);

	void 
	appendVertex(
		CEGUI::Vertex const &);

	void 
	appendGeometry(
		CEGUI::Vertex const *,
		CEGUI::uint vertex_count);

	void 
	setActiveTexture(
		CEGUI::Texture*);

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
		CEGUI::RenderEffect*);

	CEGUI::RenderEffect* 
	getRenderEffect();

	void 
	setBlendMode(
		CEGUI::BlendMode);

	CEGUI::BlendMode 
	getBlendMode() const;

	~geometry_buffer();
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
}

#endif
