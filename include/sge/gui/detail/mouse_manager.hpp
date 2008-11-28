#ifndef SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED

#include <sge/gui/skin.hpp>
#include <sge/gui/types.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/widgets/container_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/signals/scoped_connection.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/device_fwd.hpp>

#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class mouse_manager
{
	public:
	mouse_manager(
		input::system_ptr,
		image::loader_ptr,
		renderer::device_ptr,
		skin &);
	
	void widget_add(widget &);
	sprite::object const cursor() const;
	void widget_remove(widget &);
	void recalculate_focus();
	private:
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> widget_container;

	widget_container widgets;
	signals::scoped_connection ic;
	sprite::object cursor_;
	sprite::point cursor_click;
	widget *focus;

	void input_callback(input::key_pair const &);
	widget *recalculate_focus(widget &w,point const &);
	widget *do_recalculate_focus(widget &,point const &);
	widget *do_recalculate_focus(widgets::container &,point const &);
};
}
}
}

#endif
