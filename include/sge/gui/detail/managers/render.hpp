#ifndef SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED

#include <sge/gui/detail/managers/fwd.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/types.hpp>
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
namespace managers
{
class render : public submanager
{
	public:
	render(
		renderer::device_ptr,
		mouse &);
	void add(widget &);
	void draw();
	void activation(widget &,activation_state::type);
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
	mouse &mouse_;
	widget_container widgets;
	dirt_container dirt;

	void redraw_dirt();
};
}
}
}
}

#endif
