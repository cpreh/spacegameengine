#ifndef SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED
#define SGE_GUI_DETAIL_MANAGERS_MOUSE_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/detail/submanager.hpp>
#include <sge/gui/cursor.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/key_pair_fwd.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/sprite/object.hpp>

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
		cursor &);
	
	void resize(
		widgets::base &,
		dim const &);
	void reposition(
		widgets::base &,
		point const &);
	void add(widgets::base &);
	void update();
	void activation(widgets::base &,activation_state::type);
	void remove(widgets::base &);
	void recalculate_focus();
	void z(widgets::base &,depth_type);
	private:
	typedef boost::ptr_vector<
		widgets::base,
		boost::view_clone_allocator> widget_container;

	widget_container widgets;
	signal::scoped_connection const ic;
	cursor &cursor_;
	widgets::base *focus;
	bool dirty_;

	void input_callback(input::key_pair const &);
	widgets::base *recalculate_focus(widgets::base &w,point const &);
	widgets::base *do_recalculate_focus(widgets::base &,point const &);
};
}
}
}
}

#endif
