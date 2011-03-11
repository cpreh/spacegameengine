#ifndef SGE_CEGUI_DETAIL_DEFAULT_TARGET_HPP_INCLUDED
#define SGE_CEGUI_DETAIL_DEFAULT_TARGET_HPP_INCLUDED

#include <CEGUI/CEGUIRenderTarget.h>
#include <CEGUI/CEGUIRect.h>
#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

namespace CEGUI
{
class GeometryBuffer;
class RenderQueue;
class Vector2;
}

namespace sge
{
namespace cegui
{
namespace detail
{
class default_target
:
	public CEGUI::RenderTarget
{
public:
	explicit
	default_target(
		sge::renderer::device_ptr);

	void 
	draw(
		CEGUI::GeometryBuffer const &);

	void 
	draw(
		CEGUI::RenderQueue const &);

	void 
	setArea(
		CEGUI::Rect const &);

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
		CEGUI::GeometryBuffer const &,
		CEGUI::Vector2 const & p_in, 
		CEGUI::Vector2& p_out) const;

	sge::renderer::matrix4 const
	projection() const;
private:
	sge::renderer::device_ptr renderer_;
	mutable CEGUI::Rect viewport_;
};
}
}
}

#endif
