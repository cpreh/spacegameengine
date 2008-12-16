#ifndef SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_MOUSE_MANAGER_HPP_INCLUDED

#include "../skin.hpp"
#include "../types.hpp"
#include "../widget_fwd.hpp"
#include "../widgets/container_fwd.hpp"
#include "../../input/system_fwd.hpp"
#include "../../image/loader_fwd.hpp"
#include "../../input/key_pair_fwd.hpp"
#include "../../signals/scoped_connection.hpp"
#include "../../sprite/object.hpp"
#include "../../renderer/device_fwd.hpp"

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
		sge::image::loader_ptr,
		renderer::device_ptr,
		skin &);
	
	void add(widget &);
	sprite::object const cursor() const;
	void remove(widget &);
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
