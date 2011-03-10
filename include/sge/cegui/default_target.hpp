#ifndef SGE_CEGUI_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_TARGET_HPP_INCLUDED

#include <CEGUI/CEGUIRenderTarget.h>
#include <CEGUI/CEGUIGeometryBuffer.h>
#include <CEGUI/CEGUIRenderQueue.h>
#include <CEGUI/CEGUIRect.h>
#include <CEGUI/CEGUIVector.h>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/cegui/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace sge
{
namespace cegui
{
class SGE_CLASS_SYMBOL default_target
:
	public CEGUI::RenderTarget
{
public:
	SGE_CEGUI_SYMBOL explicit
	default_target(
		sge::renderer::device_ptr);

	SGE_CEGUI_SYMBOL void 
	draw(CEGUI::GeometryBuffer const &);

	SGE_CEGUI_SYMBOL void 
	draw(CEGUI::RenderQueue const &);

	SGE_CEGUI_SYMBOL void 
	setArea(CEGUI::Rect const &);

	SGE_CEGUI_SYMBOL CEGUI::Rect const &
	getArea() const;

	SGE_CEGUI_SYMBOL bool 
	isImageryCache() const;

	SGE_CEGUI_SYMBOL void 
	activate();

	SGE_CEGUI_SYMBOL void 
	deactivate();

	SGE_CEGUI_SYMBOL void 
	unprojectPoint(
		CEGUI::GeometryBuffer const &,
		CEGUI::Vector2 const & p_in, 
		CEGUI::Vector2& p_out) const;

	SGE_CEGUI_SYMBOL sge::renderer::matrix4 const
	projection() const;
private:
	sge::renderer::device_ptr renderer_;
	mutable CEGUI::Rect viewport_;
};
}
}

#endif
