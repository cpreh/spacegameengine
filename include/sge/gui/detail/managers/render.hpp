#ifndef SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_RENDER_HPP_INCLUDED

#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/cursor.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/object.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <map>

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
		cursor &);
	void add(widget &);
	void update();
	void draw();
	void activation(widget &,activation_state::type);
	void remove(widget &);
	void resize(widget &,dim const &);
	void reposition(widget &,point const &);
	void dirty(
		widget &,
		rect const &);
	sge::sprite::object &connected_sprite(widget &);
	private:
	struct widget_data
	{
		renderer::texture_ptr texture;
		sprite::object sprite;
	};

	typedef boost::ptr_map<widget*,widget_data> widget_container;
	typedef std::multimap<widget*,rect> dirt_container;

	renderer::device_ptr rend;
	sprite::system ss;
	sprite::container sprites_;
	cursor &cursor_;
	widget_container widgets;
	dirt_container dirt_;

	void clean();
};
}
}
}
}

#endif
