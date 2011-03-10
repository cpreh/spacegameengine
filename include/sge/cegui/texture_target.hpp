#ifndef SGE_CEGUI_TEXTURE_TARGET_HPP_INCLUDED
#define SGE_CEGUI_TEXTURE_TARGET_HPP_INCLUDED

#include <sge/cegui/system_fwd.hpp>
#include <sge/cegui/texture_fwd.hpp>
#include <CEGUI/CEGUITexture.h>
#include <CEGUI/CEGUITextureTarget.h>
#include <CEGUI/CEGUISize.h>
#include <CEGUI/CEGUIGeometryBuffer.h>
#include <CEGUI/CEGUIRenderQueue.h>
#include <CEGUI/CEGUIRect.h>
#include <CEGUI/CEGUIVector.h>
#include <CEGUI/CEGUISystem.h>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace cegui
{
class texture_target
:
	public CEGUI::TextureTarget
{
FCPPT_NONCOPYABLE(
	texture_target);
public:
	explicit 
	texture_target(
		system &);

	void 
	draw(
		CEGUI::GeometryBuffer const & buffer);

	void 
	draw(
		CEGUI::RenderQueue const & queue);

	void 
	setArea(
		CEGUI::Rect const & area);

	CEGUI::Rect const &
	getArea() const;

	bool 
	isImageryCache() const;

	void 
	activate();

	void 
	deactivate();

	void 
	unprojectPoint(
		CEGUI::GeometryBuffer const & buff,
		CEGUI::Vector2 const &p_in, 
		CEGUI::Vector2 & p_out) const;

	void 
	clear();

	CEGUI::Texture &
	getTexture() const;

	void 
	declareRenderSize(
		CEGUI::Size const &);

	bool 
	isRenderingInverted() const;

	~texture_target();
private:
	typedef 
	fcppt::scoped_ptr<texture> 
	texture_scoped_ptr;

	system &system_;
	sge::renderer::target_ptr target_;
	texture_scoped_ptr texture_;
	CEGUI::Rect area_;
	sge::renderer::matrix4 temp_projection_;
};
}
}

#endif
