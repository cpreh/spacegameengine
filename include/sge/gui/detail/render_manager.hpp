#ifndef SGE_GUI_DETAIL_RENDER_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_RENDER_MANAGER_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/gui/detail/manager_fwd.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <map>
#include <vector>

namespace sge
{
namespace gui
{
namespace detail
{
class render_manager
{
	public:
	render_manager(
		renderer::device_ptr,
		mouse_manager &);
	void add(widget &);
	void draw();
	void remove(widget &);
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);
	void invalidate(rect const &);
	private:
	struct widget_data
	{
		renderer::texture_ptr texture;
		sprite::object sprite;
	};

	typedef std::map<widget*,widget_data> widget_container;
	typedef std::vector<rect> dirt_container;

	renderer::device_ptr rend;
	sprite::system ss;
	mouse_manager &mouse;
	widget_container widgets;
	dirt_container dirt;

	void redraw_dirt();
};
}
}
}

#endif
