#ifndef SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/skin.hpp>
#include <sge/gui/cursor.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/image/loader_fwd.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/sprite/object.hpp>
#include <sge/renderer/device_fwd.hpp>

#include <boost/ptr_container/ptr_vector.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
namespace managers
{
class mouse : public submanager
{
	public:
	mouse(
		input::system_ptr,
		sge::image::loader_ptr,
		renderer::device_ptr,
		cursor &);
	
	void resize(
		widget &,
		dim const &);
	void reposition(
		widget &,
		point const &);
	void add(widget &);
	void update();
	void activation(widget &,activation_state::type);
	void remove(widget &);
	void recalculate_focus();
	private:
	typedef boost::ptr_vector<widget,boost::view_clone_allocator> widget_container;

	widget_container widgets;
	signal::scoped_connection const ic;
	cursor &cursor_;
	widget *focus;
	bool dirty_;

	void input_callback(input::key_pair const &);
	widget *recalculate_focus(widget &w,point const &);
	widget *do_recalculate_focus(widget &,point const &);
};
}
}
}
}

#endif
